function Qd = p4_qd(config, A, Ts, nb)
% P4_QD  Process-noise covariance Qd for the Part IV Kalman filter (test plan).
%   Qd = p4_qd(config, A, Ts, nb)
%   A  : continuous A (6x6, or 6+nb with bias states)
%   nb : number of bias states appended after the 6 physical states
%
% Baseline: process noise modelled as white unmodelled ANGULAR ACCELERATION
% on p_ddot, e_ddot and lambda_ddot, discretized exactly with Van Loan:
%     x_dot = A x + B u + G w,   E[w w'] = Qc delta(t)
%
% Test plan (diagonal ordering [p pdot e edot lambda lambdadot (biases)]):
%   Zero      Qd = 0       -> filter trusts the model completely, L -> 0,
%                             estimates become open-loop simulation (drift).
%   Inf       Qd = 1e6*I   -> filter trusts the measurements completely,
%                             x_hat ~ y (no smoothing, IMU noise passes through).
%   Low/High  Baseline x 0.01 / x 100
%   PitchHigh more process noise on the pitch channel only (x100)
%   ElevHigh  more process noise on the elevation channel only (x100)
if nargin < 4, nb = 0; end
n = size(A, 1);

% Continuous intensities [(rad/s^2)^2 * s]  -- the actual tuning knobs
q_pddot  = 0.01;     % pitch acceleration
q_eddot  = 0.005;     % elevation acceleration
q_lddot  = 0.005;     % travel acceleration
q_bias   = 1e-6;     % random walk on bias states (slowly varying)

G = zeros(n, 3 + nb);
G(2, 1) = 1;  G(4, 2) = 1;  G(6, 3) = 1;
for i = 1:nb, G(6 + i, 3 + i) = 1; end
Qc_base = diag([q_pddot, q_eddot, q_lddot, q_bias*ones(1, nb)]);

Qd_base = van_loan(A, G, Qc_base, Ts);

S_pitch = diag([100 100 1 1 1 1 ones(1,nb)]);
S_elev  = diag([1 1 100 100 1 1 ones(1,nb)]);

switch config
    case 'Baseline',  Qd = Qd_base;
    case 'Zero',      Qd = zeros(n);
    case 'Inf',       Qd = 1e6 * eye(n);
    case 'Low',       Qd = 0.01 * Qd_base;
    case 'High',      Qd = 100  * Qd_base;
    case 'PitchHigh', Qd = sqrt(S_pitch) * Qd_base * sqrt(S_pitch);
    case 'ElevHigh',  Qd = sqrt(S_elev)  * Qd_base * sqrt(S_elev);
    otherwise, error('Unknown Qd config: %s', config);
end
Qd = (Qd + Qd.') / 2;
end
