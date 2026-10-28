%% part3_observer.m - Part III, Luenberger observer
heli_params;   % K1, K2, K3, ...

%% Problem 1 - Extended state-space model
% x = [p; p_dot; e; e_dot; lambda_dot],  u = [Vs_tilde; Vd]
A_est = [0  1 0 0 0;
         0  0 0 0 0;
         0  0 0 1 0;
         0  0 0 0 0;
         K3 0 0 0 0];

B_est = [0  0;
         0  K1;
         0  0;
         K2 0;
         0  0];

%% Problem 2 - Observability
C_min = [0 0 1 0 0;     % e
         0 0 0 0 1];    % lambda_dot
rank(obsv(A_est, C_min))     % 5 -> observable

%% Problem 3 - Angles from accelerometer
% Implemented in a MATLAB Function block in Simulink (see imu_angles.m):
%   p = atan(ay/az),   e = atan(ax / sqrt(ay^2 + az^2))

%% Problem 4 - State estimator
C_full = eye(5);                         % y = [p; p_dot; e; e_dot; lambda_dot]

obs_poles = [-10 -11 -12 -13 -14];       % real, distinct, faster than controller

L     = place(A_est', C_full', obs_poles)';
L_min = place(A_est', C_min',  obs_poles)';

eig(A_est - L*C_full)                    % should match obs_poles