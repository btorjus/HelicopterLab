% Testplan:
%   1 = Alle tilstander, rask     (poler langt til venstre, mye stoy)
%   2 = Alle tilstander, treg     (poler naer imaginaeraksen, lite stoy)
%   3 = Alle tilstander, balansert
%   4 = Minimum tilstander (e, lambda_dot), rask
%   5 = Minimum tilstander (e, lambda_dot), treg
%   6 = Minimum tilstander (e, lambda_dot), balansert


heli_params;
addpath('utils');

%PORT
PORT = 4;


%% 3. Systemmatriser   x = [p; p_dot; e; e_dot; lambda_dot],  u = [Vs_tilde; Vd]
A_obs = [0  1 0 0 0;
         0  0 0 0 0;
         0  0 0 1 0;
         0  0 0 0 0;
         K3 0 0 0 0];

B_obs = [0  0;
         0  K1;
         0  0;
         K2 0;
         0  0];

C_all = eye(5);                    % alle IMU-malingene
C_min = [0 0 1 0 0;                % e
         0 0 0 0 1];               % lambda_dot
     
C_min5 = diag([0 0 0 0 1]);

% Polsett
p_fast   = [-10 -11 -12 -13 -14];  % rask / mye stoy
p_slow   = [ -1  -2  -2  -3  -3];  % treg / lite stoy
p_medium = [ -4  -5  -5  -6  -6];  % balansert

%% 4. VELG TEST HER
TEST = 1;

switch TEST
    case 1, C_obs = C_all; p_obs = p_fast;   navn = 'Alle tilstander, rask';
    case 2, C_obs = C_all; p_obs = p_slow;   navn = 'Alle tilstander, treg';
    case 3, C_obs = C_all; p_obs = p_medium; navn = 'Alle tilstander, balansert';
    case 4, C_obs = C_min; p_obs = p_fast;   navn = 'Minimum tilstander, rask';
    case 5, C_obs = C_min; p_obs = p_slow;   navn = 'Minimum tilstander, treg';
    case 6, C_obs = C_min; p_obs = p_medium; navn = 'Minimum tilstander, balansert';
end

% Observerbarhet og observatorforsterkning
assert(rank(obsv(A_obs, C_obs)) == 5, 'Systemet er ikke observerbart med denne C');
L = place(A_obs', C_obs', p_obs)';           % 5x5 (alle) eller 5x2 (minimum)

% Effektiv forsterkning mot den fulle 5x1 malevektoren y_full.
% Da trenger Simulink-modellen aldri endre dimensjon mellom testene:
%   x_hat_dot = A_obs*x_hat + B_obs*u + L_eff*(y_full - x_hat)
% Dette er det samme som L*(C_obs*y_full - C_obs*x_hat), fordi C_obs bare
% plukker ut de malte tilstandene.
L_ = L*C_obs;                             % alltid 5x5


fprintf('\nTEST %d: %s\n', TEST, navn);
fprintf('Onskede poler:   %s\n', mat2str(sort(p_obs)));
fprintf('Oppnadde poler:  %s\n', mat2str(sort(eig(A_obs - L*C_obs))', 4));
fprintf('Storste |L|-element: %.1f\n', max(abs(L(:))));
disp('L ='), disp(L)

%% 5. Oversikt over alle testene (for rapporten)
tests = {C_all,p_fast; C_all,p_slow; C_all,p_medium; ...
         C_min,p_fast; C_min,p_slow; C_min,p_medium};
navn_alle = {'Alle, rask','Alle, treg','Alle, balansert', ...
             'Min, rask','Min, treg','Min, balansert'};
fprintf('\n%-18s %12s\n', 'Test', 'max|L|');
for k = 1:6
    Lk = place(A_obs', tests{k,1}', tests{k,2})';
    fprintf('%d %-16s %12.1f\n', k, navn_alle{k}, max(abs(Lk(:))));
end

%% 6. Kontroll: ikke-observerbar C (e_dot og lambda_dot) - skal feile
C_U = [0 0 0 1 0; 0 0 0 0 1];
fprintf('\nrank(obsv) med e_dot og lambda_dot: %d (ikke observerbar)\n', ...
        rank(obsv(A_obs, C_U)));
