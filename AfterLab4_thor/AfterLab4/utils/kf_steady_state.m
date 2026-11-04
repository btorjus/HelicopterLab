function [L, P_hat] = kf_steady_state(Ad, Cd, Qd, Rd)
% KF_STEADY_STATE  Iterate the Kalman recursion (2.21) until P converges.
%   Assumes a measurement every step. Returns [] if it does not converge
%   (e.g. Qd = 0 -> P -> 0, or Qd = Inf).
n = size(Ad, 1);
P_bar = eye(n);
L = []; P_hat = [];
for k = 1:200000
    S  = Cd*P_bar*Cd.' + Rd;
    Lk = P_bar*Cd.' / S;
    IK = eye(n) - Lk*Cd;
    Ph = IK*P_bar*IK.' + Lk*Rd*Lk.';
    Pb = Ad*Ph*Ad.' + Qd;
    if norm(Pb - P_bar, 'fro') < 1e-14 * max(1, norm(P_bar, 'fro'))
        L = Lk; P_hat = Ph; return
    end
    P_bar = Pb;
end
warning('kf_steady_state: did not converge');
L = Lk; P_hat = Ph;
end
