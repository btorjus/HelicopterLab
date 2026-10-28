%% p2_lqri.m — Part II Task 2: LQR with integral action
% State:     x = [p; p_dot; e_dot; gamma; zeta]
%            gamma_dot = p_c - p,   zeta_dot = edot_c - e_dot
% Input:     u = [Vs_tilde; Vd]
% Reference: r = [p_c; edot_c]
% Control:   u = F*r - K*x
clear; clc;
heli_params;
addpath('utils');

%% ---------- Select configuration ----------
config = 'IBaseline';      % IBaseline | IHigh | ILow
use_F  = true;             % true: keep feedforward, false: F = 0 (integrator does all work)

%% ---------- Augmented model ----------
A_lqri = [ 0 1  0 0 0;
           0 0  0 0 0;
           0 0  0 0 0;
          -1 0  0 0 0;
           0 0 -1 0 0];
B_lqri = [0  0;
          0  K1;
          K2 0;
          0  0;
          0  0];
G_lqri = [0 0; 0 0; 0 0; 1 0; 0 1];

assert(rank(ctrb(A_lqri, B_lqri)) == 5, 'Augmented system not controllable');

%% ---------- Weights: Task 1 Baseline + integral weights ----------
[Q3, R] = p2_weights('Baseline');           % same as Task 1 Baseline

switch config
    case 'IBaseline', Qi = diag([1   1  ]);
    case 'IHigh',     Qi = diag([10  10 ]);  % strong integral action
    case 'ILow',      Qi = diag([0.1 0.1]);  % weak integral action
    otherwise, error('Unknown config: %s', config);
end
Q = blkdiag(Q3, Qi);

%% ---------- Gains ----------
K = lqr(A_lqri, B_lqri, Q, R);              % 2x5

if use_F
    F = [K(1,1) K(1,3);
         K(2,1) K(2,3)];
else
    F = zeros(2);
end

%% ---------- Step reference settings ----------
pc_step    = 0.3;          % [rad]   (set 0 for elevation test)
edot_pulse = 0;            % [rad/s] (set 0.1 for elevation test)
pulse_len  = 3;            % [s]

%% ---------- Report ----------
fprintf('\n=== Config: %s  (use_F = %d) ===\n', config, use_F);
disp('K ='); disp(K);
disp('F ='); disp(F);
disp('Closed-loop poles:'); disp(eig(A_lqri - B_lqri*K));
