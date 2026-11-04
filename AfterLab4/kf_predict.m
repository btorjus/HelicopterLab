function [x_bar_next, P_bar_next] = kf_predict(x_hat, P_hat, u, Ad, Bd, Qd)
% Copy of the code inside the 'kf_predict' MATLAB Function block in
% heli_p4_kalman_kf_r2020b.slx (reference/report only - the model does NOT read this file).
% If you change the block, update this copy too.
% KF_PREDICT  Prediction step (2.21d-e). Paste into a MATLAB Function block.
%   Inputs  (signals)   : x_hat [n x 1], P_hat [n x n], u = [Vs_tilde; Vd]
%   Inputs  (Parameter) : Ad, Bd, Qd   (set Scope = Parameter in the Symbols
%                         pane / Ports & Data Manager so they are read from
%                         the workspace created by p4_kalman.m)
%   Outputs             : x_bar[k+1], P_bar[k+1]  -> Unit Delay -> kf_correct
%#codegen
x_bar_next = Ad*x_hat + Bd*u;
P_bar_next = Ad*P_hat*Ad.' + Qd;
P_bar_next = 0.5*(P_bar_next + P_bar_next.');     % keep symmetric numerically
end
