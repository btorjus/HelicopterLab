%% p4_kalman.m — Part IV: discrete-time Kalman filter + LQR(I) controller
% Run this before QuaRC -> Build of heli_p4_kalman.slx.
%
% Estimator state:  x = [p; p_dot; e; e_dot; lambda; lambda_dot]   (+ biases, optional)
% Measurement:      y = [p; p_dot; e; e_dot; lambda_dot]           (IMU, after Part III transforms)
% Input:            u = [Vs_tilde; Vd]                              (controller output, before + Vs0)
%
% Controller state is DIFFERENT from estimator state (keep the two problems separate):
%   LQR :  x_ctrl = [p; p_dot; e_dot]                   -> take x_hat([1 2 4])
%   LQRI:  x_ctrl = [p; p_dot; e_dot; gamma; zeta]      -> x_hat([1 2 4]) + the two integrators
%
% Simulink (see README_part4.md):
%   kf_correct (MATLAB Fcn) : (x_bar, P_bar, y, new_data) -> (x_hat, P_hat, P_diag)
%   kf_predict (MATLAB Fcn) : (x_hat, P_hat, u)           -> (x_bar[k+1], P_bar[k+1])
%   Unit Delay x2 (IC = x0, P0) closes the loop back to kf_correct.

clear; clc;
heli_params;                 % K1, K2, K3, Vs0, ...
addpath('utils');

%PORT
PORT = 4; % Velg rikitg port for PC!!!!!

%% ======================= Select configuration ===========================
ctrl_type = 'LQRI';          % 'LQR' (no integral) | 'LQRI' (integral action)
lqr_cfg   = 'Baseline';      % weights from p2_weights (Part II)
lqri_cfg  = 'IBaseline';     % IBaseline | IHigh | ILow
use_F     = true;            % feedforward in LQRI

Qd_cfg    = 'Baseline';      % Baseline | Zero | Inf | Low | High | PitchHigh | ElevHigh
use_bias  = false;           % Bonus 2: estimate IMU biases as extra states
bias_set  = {'p','pdot','edot'};   % observable choice (see observability check below)

Ts        = 0.002;           % [s] Simulink fixed step (heli model runs at 500 Hz)

%% ======================= Controller (from Part II) ======================
switch ctrl_type
    case 'LQR'
        A_c = [0 1 0; 0 0 0; 0 0 0];
        B_c = [0 0; 0 K1; K2 0];
        [Qc_lqr, Rc_lqr] = p2_weights(lqr_cfg);
        K = lqr(A_c, B_c, Qc_lqr, Rc_lqr);              % 2x3
        F = [K(1,1) K(1,3); K(2,1) K(2,3)];
    case 'LQRI'
        A_c = [ 0 1  0 0 0;
                0 0  0 0 0;
                0 0  0 0 0;
               -1 0  0 0 0;
                0 0 -1 0 0];
        B_c = [0 0; 0 K1; K2 0; 0 0; 0 0];
        [Q3, Rc_lqr] = p2_weights(lqr_cfg);
        switch lqri_cfg
            case 'IBaseline', Qi = diag([1   1  ]);
            case 'IHigh',     Qi = diag([10  10 ]);
            case 'ILow',      Qi = diag([0.1 0.1]);
            otherwise, error('Unknown lqri_cfg: %s', lqri_cfg);
        end
        K = lqr(A_c, B_c, blkdiag(Q3, Qi), Rc_lqr);    % 2x5
        if use_F, F = [K(1,1) K(1,3); K(2,1) K(2,3)]; else, F = zeros(2); end
    otherwise
        error('Unknown ctrl_type: %s', ctrl_type);
end

% Step reference settings (same as Part II)
pc_step    = 0.3;            % [rad]
edot_pulse = 0.1;            % [rad/s]
pulse_len  = 3;              % [s]

% Reference profile for the "From Workspace" block (variable ref_profile,
% columns [t, p_c, edot_c]). Replace with your own profile from Part III if
% you had one. Pitch step 5-15 s, elevation-rate pulse 25-(25+pulse_len) s.
T_ref       = 60;                                    % [s]
t_ref       = (0:Ts:T_ref).';
pc_ref      = pc_step    * (t_ref >= 5  & t_ref < 15);
edotc_ref   = edot_pulse * (t_ref >= 25 & t_ref < 25 + pulse_len);
ref_profile = [t_ref, pc_ref, edotc_ref];

%% ======================= Problem 1: continuous model ====================
% x = [p; p_dot; e; e_dot; lambda; lambda_dot]
% Same sign convention as part3_observer.m (lambda_ddot = K3*p)
A = [0  1 0 0 0 0;
     0  0 0 0 0 0;
     0  0 0 1 0 0;
     0  0 0 0 0 0;
     0  0 0 0 0 1;
     K3 0 0 0 0 0];
B = [0  0;
     0  K1;
     0  0;
     K2 0;
     0  0;
     0  0];
C = [1 0 0 0 0 0;            % p          (accelerometer)
     0 1 0 0 0 0;            % p_dot      (gyro, transformed)
     0 0 1 0 0 0;            % e          (accelerometer)
     0 0 0 1 0 0;            % e_dot      (gyro, transformed)
     0 0 0 0 0 1];           % lambda_dot (gyro, transformed)
state_names = {'p','pdot','e','edot','lambda','lambdadot'};
meas_names  = {'p','pdot','e','edot','lambdadot'};

%% ---------- Bonus 2: bias states (y = C x + b,  b_dot = 0) ----------
if use_bias
    map = containers.Map({'p','pdot','e','edot','lambdadot'}, {1,2,3,4,5});
    nb  = numel(bias_set);
    E   = zeros(5, nb);
    for i = 1:nb, E(map(bias_set{i}), i) = 1; end
    A = blkdiag(A, zeros(nb));
    B = [B; zeros(nb, 2)];
    C = [C, E];
    state_names = [state_names, strcat('b_', bias_set)];
end
n = size(A, 1);

%% ---------- Discretize (zero-order hold, same step as Simulink) ----------
sysd = c2d(ss(A, B, C, zeros(5,2)), Ts, 'zoh');
Ad = sysd.A;  Bd = sysd.B;  Cd = sysd.C;

%% ---------- Observability ----------
r_obs = rank(obsv(Ad, Cd));
fprintf('Observability rank: %d / %d\n', r_obs, n);
if r_obs < n
    % lambda is never measured and nothing depends on it -> unobservable.
    % Its variance P(5,5) will grow without bound; that is expected
    % (and harmless, the controller does not use lambda).
    unobs = [];
    for i = 1:n
        idx = setdiff(1:n, i);
        if rank(obsv(Ad(idx,idx), Cd(:,idx))) == n-1, unobs(end+1) = i; end %#ok<SAGROW>
    end
    fprintf('  Unobservable direction(s) involve: %s\n', strjoin(state_names(unobs), ', '));
end

%% ======================= Measurement noise Rd (Task 1) ==================
Rd_file = fullfile('data', 'p4', 'Rd.mat');
if exist(Rd_file, 'file')
    S  = load(Rd_file);
    Rd = S.Rd;
    fprintf('Loaded Rd from %s (flying covariance)\n', Rd_file);
else
    Rd = diag([1e-3 1e-3 1e-3 1e-3 1e-3]);   % PLACEHOLDER until p4_noise_estimate is run
    warning('No %s found - using placeholder Rd. Run p4_noise_estimate first.', Rd_file);
end

%% ======================= Process noise Qd (tuning) ======================
Qd = p4_qd(Qd_cfg, A, Ts, use_bias * (n - 6));

%% ======================= Initial conditions =============================
% Helicopter rests on the ground at startup. Set e0 to the ground elevation
% (in the same frame as the IMU e-measurement) if you want a fast start.
e0 = 0;                      % [rad]
x0 = zeros(n, 1);  x0(3) = e0;
P0 = blkdiag(diag([0.1 0.1 0.1 0.1 0.1 0.1]), 0.01*eye(n - 6));

% Constant IMU offsets from Part III (subtract in Simulink if not estimating biases)
imu_offset = zeros(5, 1);    % [p; pdot; e; edot; lambdadot]

%% ======================= Report =========================================
if strcmp(ctrl_type, 'LQR'), ctrl_cfg = lqr_cfg; else, ctrl_cfg = lqri_cfg; end
fprintf('\n=== Controller: %s (%s)   Qd: %s   bias states: %d ===\n', ...
        ctrl_type, ctrl_cfg, Qd_cfg, n - 6);
disp('K ='); disp(K);
disp('F ='); disp(F);
disp('Closed-loop controller poles:'); disp(eig(A_c - B_c*K));
fprintf('Qd diag = [%s]\n', num2str(diag(Qd).', '%.3g  '));
fprintf('Rd diag = [%s]\n', num2str(diag(Rd).', '%.3g  '));

% Steady-state Kalman gain if a measurement arrived every step.
% lambda is unobservable, so the Riccati recursion is run on the observable
% subsystem only. The equivalent continuous-time estimator poles can be
% compared directly with the Luenberger poles chosen in Part III.
obs_idx = setdiff(1:n, 5);
[L_ss, P_ss] = kf_steady_state(Ad(obs_idx,obs_idx), Cd(:,obs_idx), ...
                               Qd(obs_idx,obs_idx), Rd);
if ~isempty(L_ss)
    z  = eig((eye(numel(obs_idx)) - L_ss*Cd(:,obs_idx)) * Ad(obs_idx,obs_idx));
    s  = log(z) / Ts;
    disp('Steady-state Kalman gain (observable states, every-step correction):');
    disp(L_ss);
    disp('Equivalent continuous estimator poles  log(z)/Ts  [rad/s]:');
    disp(s);
    fprintf('Steady-state std of estimates: [%s]\n', ...
            num2str(sqrt(diag(P_ss)).', '%.3g  '));
end
