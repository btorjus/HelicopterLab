function [x_bar_next, P_bar_next] = kf_predict(x_hat, P_hat, u, Ad, Bd, Qd)
%#codegen
% KF_PREDICT  Kalman filter prediction step (prelab eq. 2.21d-e).
% Paste this into the "Prediction" MATLAB Function block in Simulink.
% Ad, Bd, Qd: declare as Parameters (Edit Data / Symbols pane), not inputs.
% Output goes through a Unit Delay (IC: x0 / P0) into kf_correct.
x_bar_next = Ad*x_hat + Bd*u;
P_bar_next = Ad*P_hat*Ad' + Qd;
end
