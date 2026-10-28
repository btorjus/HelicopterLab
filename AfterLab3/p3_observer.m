%% p3_observer.m - Part III: Luenberger-observator
% Testplan:
%   1 = Alle tilstander, rask          (poler langt til venstre, mye stoy)
%   2 = Alle tilstander, treg          (poler naer imaginaeraksen, lite stoy)
%   3 = Alle tilstander, balansert
%   4 = Minimum tilstander (e, lambda_dot), rask
%   5 = Minimum tilstander (e, lambda_dot), treg
%   6 = Minimum tilstander (e, lambda_dot), balansert
%   7 = Alle tilstander, veldig rask
%   8 = Minimum tilstander, veldig rask
%
% Kjor KUN dette skriptet for Build. Det kjorer init-fil og regulator selv.
%
% Simulink-observator (C-forsterkningen i Simulink er eye(5)):
%   x_hat_dot = A_obs*x_hat + B_obs*u + L_obs*(y_full - x_hat)
%   u      = [Vs_tilde; Vd]   (regulatorutgang FOR Vs0 legges til)
%   y_full = [p; p_dot; e; e_dot; lambda_dot] fra IMU (etter transformasjon)
clear; clc;

%% 0. Init og regulator fra Part II
addpath('utils');
p2_lqri;              % gir A_lqri, B_lqri, K, F


ctrl_poles = eig(A_lqri - B_lqri*K);
lambda_c   = max(abs(real(ctrl_poles)));      % raskeste regulatorpol

%% 1. Innstillinger
PORT    = 4;          % IMU COM-port (sjekk Device Manager hver labdag)
TEST    = 8;          % velg test 1-8 (se over)
use_est = 1;          % 0 = regulator pa enkodere (observator gar parallelt)
                      % 1 = regulator pa estimater
                      % Kan endres under kjoring: sett verdi + Ctrl+D i Simulink

%% 2. Systemmatriser   x = [p; p_dot; e; e_dot; lambda_dot],  u = [Vs_tilde; Vd]
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

%% 3. Polsett
p_slow   = [ -1  -2  -2  -3  -3];  % treg / lite stoy
p_medium = [ -4  -5  -5  -6  -6];  % balansert
p_fast   = [-10 -11 -12 -13 -14];  % rask / mye stoy
p_vfast  = [-50 -55 -60 -65 -70];  % veldig rask / svaert mye stoy

%% 4. Velg test
switch TEST
    case 1, C_obs = C_all; p_obs = p_fast;   navn = 'Alle tilstander, rask';
    case 2, C_obs = C_all; p_obs = p_slow;   navn = 'Alle tilstander, treg';
    case 3, C_obs = C_all; p_obs = p_medium; navn = 'Alle tilstander, balansert';
    case 4, C_obs = C_min; p_obs = p_fast;   navn = 'Minimum tilstander, rask';
    case 5, C_obs = C_min; p_obs = p_slow;   navn = 'Minimum tilstander, treg';
    case 6, C_obs = C_min; p_obs = p_medium; navn = 'Minimum tilstander, balansert';
    case 7, C_obs = C_all; p_obs = p_vfast;  navn = 'Alle tilstander, veldig rask';
    case 8, C_obs = C_min; p_obs = p_vfast;  navn = 'Minimum tilstander, veldig rask';
    otherwise, error('Ukjent TEST: %d', TEST);
end

%% 5. Observerbarhet og observatorforsterkning
assert(rank(obsv(A_obs, C_obs)) == 5, 'Systemet er ikke observerbart med denne C');
L = place(A_obs', C_obs', p_obs)';           % 5x5 (alle) eller 5x2 (minimum)

% Effektiv forsterkning mot den fulle 5x1 malevektoren y_full.
% L*(C_obs*y_full - C_obs*x_hat) = (L*C_obs)*(y_full - x_hat),
% sa Simulink-modellen aldri trenger a endre dimensjon mellom testene.
L_obs = L*C_obs;                             % alltid 5x5

%% 6. Utskrift
fprintf('\n=== TEST %d: %s ===\n', TEST, navn);
fprintf('Regulatorpoler:      %s\n', mat2str(sort(real(ctrl_poles))', 3));
fprintf('Raskeste regulatorpol: %.2f\n', -lambda_c);
fprintf('Onskede poler:       %s\n', mat2str(sort(p_obs)));
fprintf('Oppnadde poler:      %s\n', mat2str(sort(real(eig(A_obs - L*C_obs)))', 4));
fprintf('Storste |L|-element: %.1f\n', max(abs(L(:))));
disp('L ='), disp(L)

% Hvor raske er polsettene i forhold til regulatoren?
% (tregeste observatorpol / raskeste regulatorpol)
fprintf('Observator vs regulator:\n');
fprintf('  treg %.1fx, balansert %.1fx, rask %.1fx, veldig rask %.1fx\n', ...
    min(abs(p_slow))/lambda_c, min(abs(p_medium))/lambda_c, ...
    min(abs(p_fast))/lambda_c, min(abs(p_vfast))/lambda_c);

% Foreslatt navn for lagring etter kjoring
modus = {'par', 'cl'};
tag   = sprintf('T3_test%d_%s', TEST, modus{use_est + 1});
fprintf('\nLagre etter kjoring med:  save_p3(''%s'')\n', tag);
fprintf('(Endrer dere use_est under kjoring: bruk _par/_cl som passer.)\n');

%% 7. Oversikt over alle testene (for rapporten)
tests = {C_all,p_fast; C_all,p_slow; C_all,p_medium; ...
         C_min,p_fast; C_min,p_slow; C_min,p_medium; ...
         C_all,p_vfast; C_min,p_vfast};
navn_alle = {'Alle, rask','Alle, treg','Alle, balansert', ...
             'Min, rask','Min, treg','Min, balansert', ...
             'Alle, v. rask','Min, v. rask'};
fprintf('\n%-18s %12s\n', 'Test', 'max|L|');
for k = 1:size(tests, 1)
    Lk = place(A_obs', tests{k,1}', tests{k,2})';
    fprintf('%d %-16s %12.1f\n', k, navn_alle{k}, max(abs(Lk(:))));
end

%% 8. Kontroll: ikke-observerbar C (e_dot og lambda_dot) - skal feile
C_U = [0 0 0 1 0; 0 0 0 0 1];
fprintf('\nrank(obsv) med e_dot og lambda_dot: %d (ikke observerbar)\n', ...
        rank(obsv(A_obs, C_U)));

%% 9. Referanseprofil (From Workspace-blokk: Data = ref_profile,
%     "Holding final value"). Utgang: [p_c; edot_c]
dt  = 0.002;  t = (0:dt:45)';
pc  = zeros(size(t));                 % pitch-referanse [rad]
edc = zeros(size(t));                 % elevasjonsrate-referanse [rad/s]

edc(t>=1  & t<4)  =  0.15;            % takeoff til ca. hover (juster lengden)
                                      % 4-8 s: stasjonaer hover (stoy, Vd-std)
pc (t>=8  & t<13) =  0.15;             % pitch-steg opp
pc (t>=13 & t<18) = -0.3;             % pitch-steg ned
edc(t>=21 & t<24) =  0.1;             % stige
edc(t>=24 & t<27) = -0.1;             % synke
idx = t>=30 & t<42;
pc(idx) = 0.2*sin(2*pi*0.3*(t(idx) - 30));   % pitch-sinus 0.3 Hz (viser etterslep)

ref_profile = [t pc edc];
