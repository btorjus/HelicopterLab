function [Q, R] = p2_weights(config)
% P2_WEIGHTS  LQR weights for Part II configs (single source of truth).
%   [Q, R] = p2_weights('Baseline')

% Bryson's rule baseline
p_max    = deg2rad(30);     % [rad]
pdot_max = 1.0;             % [rad/s]
edot_max = 0.3;             % [rad/s]
Vs_max   = 5;               % [V]
Vd_max   = 2;               % [V]

Q0 = diag([1/p_max^2, 1/pdot_max^2, 1/edot_max^2]);
R0 = diag([1/Vs_max^2, 1/Vd_max^2]);

switch config
    case 'Baseline',   Q = Q0;                  R = R0;
    case 'Aggressive', Q = 10*Q0;               R = R0;
    case 'Sluggish',   Q = Q0;                  R = 10*R0;
    case 'PitchPrio',  Q = Q0*diag([10 1 1]);   R = R0;
    case 'PitchDamp',  Q = Q0*diag([1 10 1]);   R = R0;
    case 'ElevPrio',   Q = Q0*diag([1 1 10]);   R = R0;
    case 'CheapVd',    Q = Q0;                  R = R0*diag([1 0.1]);
    otherwise, error('Unknown config: %s', config);
end
end
