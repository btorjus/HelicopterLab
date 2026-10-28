%% p2_lqr.m — Part II Task 1: LQR with reference feedforward (no integral action)
% State:     x = [p; p_dot; e_dot]
% Input:     u = [Vs_tilde; Vd]
% Reference: r = [p_c; e_dot_c]
% Control:   u = F*r - K*x
clear; clc;
heli_params;

%% ---------- Select configuration ----------
config = 'Baseline';        % Baseline | Aggressive | Sluggish | PitchPrio
                            % PitchDamp | ElevPrio | CheapVd

%% ---------- Linearized model ----------
A_lqr = [0 1 0;
         0 0 0;
         0 0 0];
B_lqr = [0   0;
         0   K1;
         K2  0];
C_ref = [1 0 0;              % picks out the tracked states p and e_dot
         0 0 1];

assert(rank(ctrb(A_lqr, B_lqr)) == 3, 'System not controllable');

%% ---------- Bryson's rule baseline ----------
p_max    = deg2rad(30);     % [rad]   acceptable pitch deviation
pdot_max = 1.0;             % [rad/s] acceptable pitch rate
edot_max = 0.3;             % [rad/s] acceptable elevation-rate error
Vs_max   = 5;               % [V]     acceptable Vs_tilde
Vd_max   = 2;               % [V]     acceptable Vd

Q0 = diag([1/p_max^2, 1/pdot_max^2, 1/edot_max^2]);   % ≈ diag(3.65, 1, 11.1)
R0 = diag([1/Vs_max^2, 1/Vd_max^2]);                  % = diag(0.04, 0.25)

%% ---------- Configurations (change one thing at a time) ----------
switch config
    case 'Baseline'
        Q = Q0;                          R = R0;
    case 'Aggressive'                    % cheaper to use input -> faster
        Q = 10*Q0;                       R = R0;
    case 'Sluggish'                      % expensive input -> slower
        Q = Q0;                          R = 10*R0;
    case 'PitchPrio'                     % tight pitch tracking
        Q = Q0*diag([10 1 1]);           R = R0;
    case 'PitchDamp'                     % penalize pitch rate -> less overshoot
        Q = Q0*diag([1 10 1]);           R = R0;
    case 'ElevPrio'                      % tight elevation-rate tracking
        Q = Q0*diag([1 1 10]);           R = R0;
    case 'CheapVd'                       % aggressive pitch actuation
        Q = Q0;                          R = R0*diag([1 0.1]);
    otherwise
        error('Unknown config: %s', config);
end

%% ---------- LQR gain and feedforward ----------
K = lqr(A_lqr, B_lqr, Q, R);

F = [K(1,1) K(1,3);
     K(2,1) K(2,3)];

% Sanity check against the general steady-state formula
F_check = inv(C_ref/(B_lqr*K - A_lqr)*B_lqr);
assert(norm(F - F_check) < 1e-9, 'F mismatch');

%% ---------- Step reference settings (for the Step/Pulse blocks) ----------
pc_step    = 0.3; %0.3;           % [rad]   pitch step amplitude
edot_pulse = 0.1; %0.1;           % [rad/s] elevation-rate pulse amplitude
pulse_len  = 3;             % [s]     pulse duration (avoid hitting end stops)

%% ---------- Report ----------
cl_poles = eig(A_lqr - B_lqr*K);
fprintf('\n=== Config: %s ===\n', config);
fprintf('Q = diag(%s)\n', num2str(diag(Q).', '%.3g  '));
fprintf('R = diag(%s)\n', num2str(diag(R).', '%.3g  '));
disp('K ='); disp(K);
disp('F ='); disp(F);
disp('Closed-loop poles:'); disp(cl_poles);