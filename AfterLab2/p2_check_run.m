%% p2_check_run.m — Quick look + sanity check of one Part II run
% Usage: set run_name, run the script from the heli_lab folder.
clear; clc;
addpath('utils');

run_name = 'Baseline_pitch';        % <-- change to the run you want to check

r = load_run_p2(run_name);
t = r.t;

%% ---------- 1. Data sanity checks ----------
fprintf('\n=== %s ===\n', run_name);
dt = median(diff(t));
fprintf('Duration: %.1f s, samples: %d, sample time: %.4f s\n', t(end)-t(1), numel(t), dt);

fields = {'p','p_rate','e','e_rate','pc','edot_c','Vs_til','Vd'};
for k = 1:numel(fields)
    if any(~isfinite(r.(fields{k})))
        warning('NaN/Inf found in %s', fields{k});
    end
end

idx0 = find(abs(r.pc) > 1e-6, 1);          % first sample where the pitch step is active
has_step = ~isempty(idx0);
if has_step
    t0 = t(idx0);
    fprintf('Pitch step detected at t = %.2f s, amplitude %.3f rad (%.1f deg)\n', ...
            t0, r.pc(end), rad2deg(r.pc(end)));
    if t(end) - t0 < 10
        warning('Less than 10 s recorded after the step — increase the QuaRC trigger duration.');
    end
else
    warning('No pitch step found in p_c — is this an elevation run, or was pc_step = 0?');
end

if any(abs(r.edot_c) > 1e-6)
    fprintf('Note: elevation-rate reference is non-zero in this run.\n');
end

%% ---------- 2. Step-response metrics ----------
if has_step
    A      = r.pc(end);                                  % reference value after step
    pre    = t >= t0-2 & t < t0;                         % 2 s of hover before the step
    post   = t >= t0;
    tail   = t >= t(end)-3;                              % last 3 s = "steady state"

    p0     = mean(r.p(pre));                             % pitch before step
    p_ss   = mean(r.p(tail));                            % pitch at the end
    tt     = t(post) - t0;
    y      = r.p(post) - p0;                             % response relative to start
    dy     = p_ss - p0;                                  % actual change achieved

    i10 = find(y >= 0.1*dy, 1);  i90 = find(y >= 0.9*dy, 1);
    if ~isempty(i10) && ~isempty(i90)
        t_rise = tt(i90) - tt(i10);
    else
        t_rise = NaN;
    end

    OS_final = (max(y) - dy)/abs(dy)*100;                % overshoot vs. where it settled
    OS_ref   = (max(r.p(post)) - A)/abs(A)*100;          % overshoot vs. reference

    band  = 0.05*abs(dy);                                % 5 % settling band
    out   = find(abs(y - dy) > band, 1, 'last');
    t_set = NaN; if ~isempty(out), t_set = tt(out); end

    e_ss  = A - p_ss;                                    % steady-state pitch error

    e0    = mean(r.e(pre));
    e_drop = min(r.e(post)) - e0;                        % elevation loss during pitch step

    fprintf('\n--- Pitch response ---\n');
    fprintf('Pitch before step:        %7.2f deg\n', rad2deg(p0));
    fprintf('Pitch at steady state:    %7.2f deg (ref %.2f deg)\n', rad2deg(p_ss), rad2deg(A));
    fprintf('Steady-state error:       %7.2f deg\n', rad2deg(e_ss));
    fprintf('Rise time (10-90 %%):      %7.2f s\n', t_rise);
    fprintf('Settling time (5 %%):      %7.2f s\n', t_set);
    fprintf('Overshoot (vs final):     %7.1f %%\n', OS_final);
    fprintf('Overshoot (vs reference): %7.1f %%\n', OS_ref);
    fprintf('\n--- Coupling / effort ---\n');
    fprintf('Elevation drop in step:   %7.2f deg\n', rad2deg(e_drop));
    fprintf('Peak |Vs_tilde|:          %7.2f V\n', max(abs(r.Vs_til(post))));
    fprintf('Peak |Vd|:                %7.2f V\n', max(abs(r.Vd(post))));
    fprintf('Pitch-rate noise (std, pre-step): %.4f rad/s\n', std(r.p_rate(pre)));
end

%% ---------- 3. Overview plot ----------
fig = figure('Color','w','Name',run_name,'Position',[100 100 1100 750]);
tl  = tiledlayout(3,2,'TileSpacing','compact','Padding','compact');
title(tl, strrep(run_name,'_',' '));

nexttile; hold on; grid on
plot(t, rad2deg(r.p), 'LineWidth',1.2)
plot(t, rad2deg(r.pc), 'k--', 'LineWidth',1)
ylabel('Pitch [deg]'); legend('p','p_c','Location','best')

nexttile; hold on; grid on
plot(t, rad2deg(r.p_rate), 'LineWidth',1)
ylabel('Pitch rate [deg/s]')

nexttile; hold on; grid on
plot(t, rad2deg(r.e_rate), 'LineWidth',1.2)
plot(t, rad2deg(r.edot_c), 'k--', 'LineWidth',1)
ylabel('Elevation rate [deg/s]'); legend('\dot{e}','\dot{e}_c','Interpreter','tex','Location','best')

nexttile; hold on; grid on
plot(t, rad2deg(r.e), 'LineWidth',1.2)
ylabel('Elevation [deg]')

nexttile; hold on; grid on
plot(t, rad2deg(r.travel_rate), 'LineWidth',1.2)
ylabel('Travel rate [deg/s]'); xlabel('Time [s]')

nexttile; hold on; grid on
plot(t, r.Vs_til, 'LineWidth',1.2)
plot(t, r.Vd, 'LineWidth',1.2)
ylabel('Voltage [V]'); xlabel('Time [s]')
legend('\tilde{V}_s','V_d','Interpreter','tex','Location','best')

if has_step
    for ax = findall(fig,'Type','axes')'
        xline(ax, t0, ':', 'HandleVisibility','off');
    end
end

%% ---------- 4. (Optional) export ----------
% if ~exist('figures','dir'), mkdir('figures'); end
% exportgraphics(fig, fullfile('figures',[run_name '_check.pdf']), 'ContentType','vector');
