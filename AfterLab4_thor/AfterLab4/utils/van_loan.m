function Qd = van_loan(A, G, Qc, Ts)
% VAN_LOAN  Exact discretization of continuous process noise (Bonus task 1).
%   Qd = van_loan(A, G, Qc, Ts)  for  x_dot = A x + G w,  E[w w'] = Qc delta(t)
%
%   M   = [ -A   G Qc G' ;  0   A' ] * Ts
%   eM  = expm(M) = [ ...  Phi^-1 Qd ;  0   Phi' ]
%   Phi = (lower-right block)',  Qd = Phi * (upper-right block)
n  = size(A, 1);
M  = [-A, G*Qc*G.'; zeros(n), A.'] * Ts;
eM = expm(M);
Phi = eM(n+1:end, n+1:end).';
Qd  = Phi * eM(1:n, n+1:end);
Qd  = (Qd + Qd.') / 2;
end
