%% p4_kalman.m - Part IV: discrete-time Kalman filter
% Run ONLY this script before Build. It runs p4_controller (-> heli_params,
% init_heli_3_10, LQR with integral action), then sets up the Kalman filter.
%
% Test plan (TEST):
%   Prelab hypotheses
%   1 = Baseline       uniform, moderate Qd                     (reference)
%   2 = Qd_zero        Qd = 0      -> trust model, L -> 0, drift   (H1)
%   3 = Qd_inf         Qd huge     -> trust IMU, noisy estimates   (H2)
%   4 = RatesHigh      high q on rates (p_dot, e_dot, lambda_dot)  (H3)
%   5 = AnglesHigh     high q on angles (p, e, lambda)             (H3)
%   Lab-day tasks (baseline filter)
%   0 = Noise          Task 1: log on the ground and in hover -> p4_noise.m
%   6 = NewDataSwitch  Task 3: cut/reconnect new-data, watch x_hat and P_hat
%   7 = VsLuenberger   Task 3: same ref_profile as Part III, compare with T3_test*_cl
%   Bonus
%   8 = VanLoan        Qd from Van Loan's method (Lec 10, slide 28), same intensity as Baseline
%
% Kalman filter in Simulink (6 states, 5 measurements):
%   x = [p; p_dot; e; e_dot; lambda; lambda_dot]
%   u = [Vs_tilde; Vd]          (controller output BEFORE Vs0 is added)
%   y = [p; p_dot; e; e_dot; lambda_dot]   from IMU (after transformation)
%   Controller states [p; p_dot; e_dot] = x_hat([1 2 4])
%
% Qd, Rd_use are tunable while running (same dimensions): change, then Ctrl+D.
% Tip for TEST 2: take off on Baseline, then set Qd = zeros(6) + Ctrl+D in hover.

p4_controller;        % clear; clc; heli_params; -> K, F, A_lqri, B_lqri, ...

%% 1. Settings
TEST    = 1;          % choose test 0-8 (see above)
use_est = 0;          % 0 = controller on encoders (filter runs in parallel)
                      % 1 = controller on Kalman estimates
                      % Can be changed while running: set value + Ctrl+D
% IMU port: set in the IMU block URI in Simulink (currently serial://IMU:9),
% check Device Manager every lab day.

%% 2. Continuous model -> discrete (exact ZOH)
T_kf = 0.002;         % Simulink fixed step

A_kf = [0  1 0 0 0 0;
        0  0 0 0 0 0;
        0  0 0 1 0 0;
        0  0 0 0 0 0;
        0  0 0 0 0 1;
        K3 0 0 0 0 0];
B_kf = [0  0;
        0  K1;
        0  0;
        K2 0;
        0  0;
        0  0];
C_kf = [eye(4), zeros(4,2);
        0 0 0 0 0 1];                    % lambda is NOT measured

sys_kf = c2d(ss(A_kf, B_kf, C_kf, 0), T_kf);
Ad = sys_kf.A;
Bd = sys_kf.B;
Cd = sys_kf.C;

fprintf('Observability rank: %d of 6 (lambda unobservable)\n', rank(obsv(Ad, Cd)));

%% 3. Measurement noise Rd (lab Task 1, computed by p4_noise.m)
if isfile('Rd_flying.mat')
    load('Rd_flying.mat', 'Rd');
    fprintf('Loaded measured Rd from Rd_flying.mat\n');
else
    Rd = diag([1e-3 1e-3 1e-3 1e-3 1e-3]);   % PLACEHOLDER until Task 1
    warning('Rd_flying.mat not found - using placeholder Rd');
end

%% 4. Process noise Qd (tuning) and initial conditions
q_low  = 1e-8;        % "small" q
q_mid  = 1e-5;        % baseline q (uniform)
q_high = 1e-2;        % "large" q
Qd_base = q_mid*eye(6);

%% Bonus 1: Van Loan's method (Lec 10, slide 28)
% exp([A, G*Qw*G'; 0, -A'] * T) = [M11 M12; 0 M22],  Ad = M11,  Qd = M12*M11'
% Continuous noise intensity Qw chosen so that Qd_vl has the same diagonal as
% Qd_base (Qd ~ G*Qw*G'*T for small T). Van Loan adds the exact off-diagonal terms.
G_kf  = eye(6);                          % noise on every state derivative
Qw_kf = Qd_base / T_kf;                  % continuous intensity
n_kf  = size(A_kf, 1);
M_vl  = expm([A_kf, G_kf*Qw_kf*G_kf'; zeros(n_kf), -A_kf'] * T_kf);
M11   = M_vl(1:n_kf, 1:n_kf);
M12   = M_vl(1:n_kf, n_kf+1:end);
Qd_vl = M12 * M11';
Qd_vl = (Qd_vl + Qd_vl')/2;              % remove round-off asymmetry

fprintf('Van Loan: max|M11 - Ad| = %.1e (should be ~0)\n', max(abs(M11(:) - Ad(:))));
fprintf('Van Loan: largest off-diagonal in Qd_vl = %.2e (diagonal = %.1e)\n', ...
        max(abs(Qd_vl(~eye(n_kf)))), q_mid);

P0 = eye(6);          % initial error covariance (Unit Delay initial condition)
x0 = zeros(6,1);      % initial estimate        (Unit Delay initial condition)
Rd_use = Rd;

%            x = [p      p_dot   e      e_dot   lambda lambda_dot]
switch TEST
    case 0, name = 'Noise';         Qd = Qd_base;
    case 1, name = 'Baseline';      Qd = Qd_base;
    case 2, name = 'Qd_zero';       Qd = zeros(6);
    case 3, name = 'Qd_inf';        Qd = 1e6*eye(6);
    case 4, name = 'RatesHigh';     Qd = diag([q_low  q_high q_low  q_high q_low  q_high]);
    case 5, name = 'AnglesHigh';    Qd = diag([q_high q_low  q_high q_low  q_high q_low ]);
    case 6, name = 'NewDataSwitch'; Qd = Qd_base;
    case 7, name = 'VsLuenberger';  Qd = Qd_base;   % or your best Qd from tests 1-5
    case 8, name = 'VanLoan';       Qd = Qd_vl;
    otherwise, error('Unknown TEST: %d', TEST);
end

%% 5. Printout
fprintf('\nTEST %d: %s   (use_est = %d)\n', TEST, name, use_est);
fprintf('diag(Qd)     = [%s]\n', sprintf('%.1e ', diag(Qd)));
fprintf('diag(Rd_use) = [%s]\n', sprintf('%.1e ', diag(Rd_use)));
modus = {'par', 'cl'};
if TEST == 0
    fprintf('After the runs: save_run_p4(''T4_noise_ground'') and save_run_p4(''T4_noise_hover''), then run p4_noise\n');
else
    tag = sprintf('T4_test%d_%s', TEST, modus{use_est + 1});
    fprintf('After the run: save_run_p4(''%s'')\n', tag);
end
if use_est && any(TEST == [2 3])
    warning('Closed loop on a limit case (Qd=0 or Qd=inf) - spotter at the counterweight!');
end

%% 6. Reference profile (copied from p3_observer.m, section 9)
%    From Workspace block: Data = ref_profile, "Holding final value". Output: [p_c; edot_c]
dt  = 0.002;  t = (0:dt:45)';
pc  = zeros(size(t));                 % pitch-referanse [rad]
edc = zeros(size(t));                 % elevasjonsrate-referanse [rad/s]

edc(t>=1  & t<4)  =  0.15;            % takeoff til ca. hover (juster lengden)
                                      % 4-8 s: stasjonaer hover (stoy, Vd-std)
pc (t>=8  & t<13) =  0.15;             % pitch-steg opp
pc (t>=13 & t<18) = -0.3;             % pitch-steg ned
edc(t>=21 & t<24) =  0.1;             % stige
edc(t>=24 & t<27) = -0.1;             % synke
idx = t>=30 & t<42;
pc(idx) = 0.2*sin(2*pi*0.3*(t(idx) - 30));   % pitch-sinus 0.3 Hz (viser etterslep)

ref_profile = [t pc edc];
