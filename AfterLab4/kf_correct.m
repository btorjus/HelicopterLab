function [x_hat, P_hat, P_diag] = kf_correct(x_bar, P_bar, y, new_data, Cd, Rd)
% Copy of the code inside the 'kf_correct' MATLAB Function block in
% heli_p4_kalman_kf_r2020b.slx (reference/report only - the model does NOT read this file).
% If you change the block, update this copy too.
% KF_CORRECT  Correction step (2.21a-c), only when new IMU data has arrived.
%   Paste into a MATLAB Function block.
%   Inputs  (signals)   : x_bar [n x 1], P_bar [n x n] (from the Unit Delays),
%                         y [5 x 1] IMU measurement, new_data (0/1, via Manual Switch)
%   Inputs  (Parameter) : Cd, Rd
%   Outputs             : x_hat, P_hat (to controller + kf_predict),
%                         P_diag = diag(P_hat) for scopes / logging
%
%   No new data:  x_hat = x_bar,  P_hat = P_bar   (eq. 2.2-2.3 in the assignment)
%#codegen
n = numel(x_bar);
if new_data > 0.5
    S     = Cd*P_bar*Cd.' + Rd;
    L     = (P_bar*Cd.') / S;                       % Kalman gain
    x_hat = x_bar + L*(y - Cd*x_bar);
    IKC   = eye(n) - L*Cd;
    P_hat = IKC*P_bar*IKC.' + L*Rd*L.';             % Joseph form
    P_hat = 0.5*(P_hat + P_hat.');
else
    x_hat = x_bar;
    P_hat = P_bar;
end
P_diag = diag(P_hat);
end
