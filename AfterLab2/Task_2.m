%% Task 2
mc = 1.92;
lc = 0.46;
mp = 0.72;
ln = 0.66;
g = 9.81;
Vs0 = 7.3;
lp = 0.175;

Kf = (-(mc*lc - 2*mp*ln)*g) / (ln*Vs0);

K1 = Kf/(2*mp*lp);
%% Rename file
copyfile('Heli3D.mat', 'HeliRun_MSStep04.mat', 'f');
copyfile('pitchdata.mat', 'pitchdataRun_MSStep04.mat', 'f');
copyfile('Vs.mat', 'Vs_MSStep04.mat', 'f');

%% Plotting
d = load_run('UDStep02');

figure;
%subplot(3,1,1)
plot(d.t, rad2deg(d.p_c), '--', d.t, rad2deg(d.pitch), 'LineWidth', 1.2)
ylabel('Pitch [deg]'); legend('Reference p_c','Measured p'); grid on
title('Critically damped step response')

% subplot(3,1,2)
% plot(d.t, d.Vd, 'LineWidth', 1.2)
% ylabel('V_d [V]'); grid on
% yline(max(abs(d.Vd)), '--r'); % quick visual check for saturation ceiling

% subplot(3,1,3)
% plot(d.t, d.Vs, 'LineWidth', 1.2)
% ylabel('V_s [V]'); xlabel('Time [s]'); grid on

%%
% pitchdataRun_<Config>.mat -> [time; p_c; error; Kpp; Kpd; Vd]
% HeliRun_<Config>.mat      -> [time; Travel; TravelRate; Pitch; PitchRate; Elevation; ElevationRate]
% Vs_<Config>.mat           -> [time; Vs]

function d = load_run(UDStep02)
    % config e.g. 'CDStep02' -- must match filename suffix EXACTLY (case-sensitive)

    pitch = load(['pitchdataRun_' UDStep02 '.mat']);
    heli  = load(['HeliRun_'      UDStep02 '.mat']);
    vs    = load(['Vs_'           UDStep02 '.mat']);

    pitch_arr = pitch.(char(fieldnames(pitch)));
    heli_arr  = heli.(char(fieldnames(heli)));
    vs_arr    = vs.(char(fieldnames(vs)));

    % --- pitch data ---
    d.t       = pitch_arr(1,:);   % use this as the reference time vector
    d.p_c     = pitch_arr(2,:);
    d.error   = pitch_arr(3,:);
    d.Kpp     = pitch_arr(4,:);
    d.Kpd     = pitch_arr(5,:);
    d.Vd      = pitch_arr(6,:);

    % --- heli data ---
    d.travel      = heli_arr(2,:);
    d.travel_rate = heli_arr(3,:);
    d.pitch       = heli_arr(4,:);
    d.pitch_rate  = heli_arr(5,:);
    d.elevation   = heli_arr(6,:);
    d.elev_rate   = heli_arr(7,:);

    % --- Vs ---
    d.Vs = vs_arr(2,:);

    % sanity check: time vectors should match in length across the 3 files
    if length(heli_arr(1,:)) ~= length(d.t) || length(vs_arr(1,:)) ~= length(d.t)
        warning('Time vector length mismatch between the 3 files for run %s — check logging rates.', UDStep02);
    end
end


