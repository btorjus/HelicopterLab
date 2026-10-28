function [x_hat, P_hat] = kf_correct(x_bar, P_bar, y, new_data, Cd, Rd_use)
%#codegen
% KF_CORRECT  Kalman filter correction step (prelab eq. 2.21a-c), Joseph form.
% Paste this into the "Correction" MATLAB Function block in Simulink.
% Cd, Rd_use: declare as Parameters (Edit Data / Symbols pane), not inputs.
% new_data must be double (use Data Type Conversion on the IMU flag, as in Part III).
if new_data > 0.5
    S     = Cd*P_bar*Cd' + Rd_use;
    L     = (P_bar*Cd')/S;
    x_hat = x_bar + L*(y - Cd*x_bar);
    IKC   = eye(6) - L*Cd;
    P_hat = IKC*P_bar*IKC' + L*Rd_use*L';
else
    x_hat = x_bar;            % no new IMU data: keep prediction
    P_hat = P_bar;
end
end
