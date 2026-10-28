%% p2_compare.m — Part II: check all runs, compute metrics, make overlay plots
% Run from the heli_lab folder. Needs utils/load_run_p2.m and utils/p2_weights.m
clear; clc; close all;
addpath('utils');
heli_params;

set(groot,'defaultTextInterpreter','latex');
set(groot,'defaultLegendInterpreter','latex');
set(groot,'defaultAxesTickLabelInterpreter','latex');

A_lqr = [0 1 0; 0 0 0; 0 0 0];
B_lqr = [0 0; 0 K1; K2 0];

cols = cellfun(@hex2rgb, {'#3B9AB2','#F21A00','#E1AF00','#78B7C5'}, 'UniformOutput', false);
cref = hex2rgb('#5B1A18');

pitch_cfgs = {'Baseline','Aggressive','Sluggish','PitchPrio','PitchDamp','CheapVd'};
elev_cfgs  = {'Baseline','Aggressive','Sluggish','ElevPrio'};

%% ---------- Load runs + data quality check ----------
fprintf('=== Data quality check ===\n');
SP = struct();  SE = struct();
for k = 1:numel(pitch_cfgs)
    c = pitch_cfgs{k};  d = try_load([c '_pitch']);
    if isempty(d), continue; end
    m = pitch_metrics(d);  check_run([c '_pitch'], d, m.t0, m.after);
    if ~m.settled && ~isnan(m.t0)
        fprintf('   -> pitch has not clearly settled; steady-state numbers are approximate\n');
    end
    SP.(c) = struct('d', d, 'm', m);
end
for k = 1:numel(elev_cfgs)
    c = elev_cfgs{k};  d = try_load([c '_elev']);
    if isempty(d), continue; end
    m = elev_metrics(d);  check_run([c '_elev'], d, m.t0, m.after);
    SE.(c) = struct('d', d, 'm', m);
end
DB = try_load('Baseline_both');

%% ---------- Theoretical closed-loop poles ----------
fprintf('\n=== Closed-loop poles (theory) ===\n');
all_cfgs = unique([pitch_cfgs elev_cfgs], 'stable');
for k = 1:numel(all_cfgs)
    c = all_cfgs{k};
    [Q, R] = p2_weights(c);
    K  = lqr(A_lqr, B_lqr, Q, R);
    pl = eig(A_lqr - B_lqr*K);
    fprintf('%-11s %s\n', c, strjoin(arrayfun(@pole_str, pl, 'UniformOutput', false), ',  '));
end

%% ---------- Metric tables (command window + LaTeX rows) ----------
fprintf('\n=== Pitch step metrics ===\n');
fprintf('%-11s %8s %8s %8s %9s %9s %10s\n','Config','tr [s]','ts [s]','OS [%]','ess[deg]','|Vd|pk[V]','e drop[deg]');
fn = fieldnames(SP);
for k = 1:numel(fn)
    m = SP.(fn{k}).m;
    fprintf('%-11s %8.2f %8.2f %8.1f %9.2f %9.2f %10.2f\n', fn{k}, m.tr, m.ts, m.OS, rad2deg(m.ess), m.Vdpk, rad2deg(m.edrop));
end
fprintf('\n%% LaTeX rows: Config & t_r & t_s & OS & e_ss & |V_d|_pk & e drop\n');
for k = 1:numel(fn)
    m = SP.(fn{k}).m;
    fprintf('%s & %.2f & %.2f & %.1f & %.2f & %.2f & %.2f \\\\\n', fn{k}, m.tr, m.ts, m.OS, rad2deg(m.ess), m.Vdpk, rad2deg(m.edrop));
end

fprintf('\n=== Elevation-rate pulse metrics ===\n');
fprintf('%-11s %8s %12s %12s %13s %10s\n','Config','tr [s]','plat.err[d/s]','RMS err[d/s]','drift [d/s]','|Vs|pk[V]');
fn = fieldnames(SE);
for k = 1:numel(fn)
    m = SE.(fn{k}).m;
    fprintf('%-11s %8.2f %12.2f %12.2f %13.2f %10.2f\n', fn{k}, m.tr, rad2deg(m.plat_err), rad2deg(m.rms), rad2deg(m.drift), m.Vspk);
end
fprintf('\n%% LaTeX rows: Config & t_r & plateau err & RMS err & drift & |Vs~|_pk\n');
for k = 1:numel(fn)
    m = SE.(fn{k}).m;
    fprintf('%s & %.2f & %.2f & %.2f & %.2f & %.2f \\\\\n', fn{k}, m.tr, rad2deg(m.plat_err), rad2deg(m.rms), rad2deg(m.drift), m.Vspk);
end

%% ---------- Figures ----------
if ~exist('figures','dir'), mkdir('figures'); end
xl = [-2 20];

% 1) Pitch: overall weight scaling
f1 = figure('Color','w','Position',[100 100 800 600]);
tiledlayout(2,1,'TileSpacing','compact');
ax = nexttile; overlay(ax, SP, {'Baseline','Aggressive','Sluggish'}, 'p', 180/pi, cols);
add_ref(ax, SP, 'Baseline', 'pc', 180/pi, cref, '$p_c$');
ylabel('Pitch [deg]'); xlim(xl); legend('Location','southeast');
ax = nexttile; overlay(ax, SP, {'Baseline','Aggressive','Sluggish'}, 'Vd', 1, cols);
ylabel('$V_d$ [V]'); xlabel('Time since step [s]'); xlim(xl);
save_fig(f1, 'p2_pitch_overall');

% 2) Pitch: individual weights
f2 = figure('Color','w','Position',[150 150 800 600]);
tiledlayout(2,1,'TileSpacing','compact');
ax = nexttile; overlay(ax, SP, {'Baseline','PitchPrio','PitchDamp','CheapVd'}, 'p', 180/pi, cols);
add_ref(ax, SP, 'Baseline', 'pc', 180/pi, cref, '$p_c$');
ylabel('Pitch [deg]'); xlim(xl); legend('Location','southeast');
ax = nexttile; overlay(ax, SP, {'Baseline','PitchPrio','PitchDamp','CheapVd'}, 'Vd', 1, cols);
ylabel('$V_d$ [V]'); xlabel('Time since step [s]'); xlim(xl);
save_fig(f2, 'p2_pitch_weights');

% 3) Elevation rate
f3 = figure('Color','w','Position',[200 200 800 800]);
tiledlayout(3,1,'TileSpacing','compact');
ax = nexttile; overlay(ax, SE, {'Baseline','Aggressive','Sluggish','ElevPrio'}, 'e_rate', 180/pi, cols);
add_ref(ax, SE, 'Baseline', 'edot_c', 180/pi, cref, '$\dot{e}_c$');
ylabel('$\dot{e}$ [deg/s]'); xlim(xl); legend('Location','northeast');
ax = nexttile; overlay(ax, SE, {'Baseline','Aggressive','Sluggish','ElevPrio'}, 'e', 180/pi, cols);
ylabel('Elevation [deg]'); xlim(xl);
ax = nexttile; overlay(ax, SE, {'Baseline','Aggressive','Sluggish','ElevPrio'}, 'Vs_til', 1, cols);
ylabel('$\tilde{V}_s$ [V]'); xlabel('Time since pulse start [s]'); xlim(xl);
save_fig(f3, 'p2_elev_overall');

% 4) Coupling run
if ~isempty(DB)
    i0 = find(abs(DB.pc) > 1e-6, 1);  t0 = DB.t(i0);  tt = DB.t - t0;
    f4 = figure('Color','w','Position',[250 250 800 800]);
    tiledlayout(4,1,'TileSpacing','compact');
    nexttile; hold on; grid on
    plot(tt, rad2deg(DB.p), 'Color', cols{1}, 'LineWidth', 1.3, 'DisplayName', '$p$');
    plot(tt, rad2deg(DB.pc), '--', 'Color', cref, 'LineWidth', 1, 'DisplayName', '$p_c$');
    ylabel('Pitch [deg]'); legend('Location','southeast'); xlim(xl);
    nexttile; hold on; grid on
    plot(tt, rad2deg(DB.e_rate), 'Color', cols{1}, 'LineWidth', 1.3, 'DisplayName', '$\dot{e}$');
    plot(tt, rad2deg(DB.edot_c), '--', 'Color', cref, 'LineWidth', 1, 'DisplayName', '$\dot{e}_c$');
    ylabel('$\dot{e}$ [deg/s]'); legend('Location','northeast'); xlim(xl);
    nexttile; grid on
    plot(tt, rad2deg(DB.travel_rate), 'Color', cols{3}, 'LineWidth', 1.3);
    ylabel('Travel rate [deg/s]'); xlim(xl);
    nexttile; hold on; grid on
    plot(tt, DB.Vs_til, 'Color', cols{1}, 'LineWidth', 1.3, 'DisplayName', '$\tilde{V}_s$');
    plot(tt, DB.Vd, 'Color', cols{2}, 'LineWidth', 1.3, 'DisplayName', '$V_d$');
    ylabel('Voltage [V]'); xlabel('Time since step [s]'); legend('Location','best'); xlim(xl);
    save_fig(f4, 'p2_coupling');
end

%% ======================= Local functions =======================
function d = try_load(name)
    d = [];
    try
        d = load_run_p2(name);
    catch
        fprintf('[MISSING] %s\n', name);
    end
end

function check_run(name, d, t0, after)
    issues = {};
    f = {'p','p_rate','e','e_rate','pc','edot_c','Vs_til','Vd'};
    for k = 1:numel(f)
        if any(~isfinite(d.(f{k}))), issues{end+1} = ['NaN in ' f{k}]; end %#ok<AGROW>
    end
    if isnan(t0), issues{end+1} = 'no step/pulse found'; end
    if ~isnan(after) && after < 15
        issues{end+1} = sprintf('only %.1f s recorded after event', after);
    end
    if isempty(issues)
        fprintf('[OK]      %-18s %.1f s total\n', name, d.t(end) - d.t(1));
    else
        fprintf('[CHECK]   %-18s %s\n', name, strjoin(issues, '; '));
    end
end

function m = pitch_metrics(d)
    t = d.t;
    m = struct('t0',NaN,'after',NaN,'tr',NaN,'ts',NaN,'OS',NaN,'ess',NaN, ...
               'Vdpk',NaN,'edrop',NaN,'settled',false);
    i0 = find(abs(d.pc) > 1e-6, 1);
    if isempty(i0), return; end
    t0 = t(i0);  A = d.pc(end);
    pre  = t >= t0-2 & t < t0;
    post = t >= t0;
    tail = t >= t(end)-3;
    p0 = mean(d.p(pre));  pss = mean(d.p(tail));
    tt = t(post) - t0;  y = d.p(post) - p0;  dy = pss - p0;
    i10 = find(y >= 0.1*dy, 1);  i90 = find(y >= 0.9*dy, 1);
    if ~isempty(i10) && ~isempty(i90), m.tr = tt(i90) - tt(i10); end
    m.OS = max(0, (max(y) - dy)/abs(dy)*100);
    out = find(abs(y - dy) > 0.05*abs(dy), 1, 'last');
    if ~isempty(out), m.ts = tt(out); else, m.ts = 0; end
    m.settled = (tt(end) - m.ts) > 3;
    m.ess   = A - pss;
    m.Vdpk  = max(abs(d.Vd(post)));
    m.edrop = min(d.e(post)) - mean(d.e(pre));
    m.t0 = t0;  m.after = t(end) - t0;
end

function m = elev_metrics(d)
    t = d.t;
    m = struct('t0',NaN,'after',NaN,'tr',NaN,'plat_err',NaN,'rms',NaN, ...
               'drift',NaN,'Vspk',NaN);
    idx = find(abs(d.edot_c) > 1e-6);
    if isempty(idx), return; end
    brk  = find(diff(idx) > 1, 1);                 % end of first pulse only
    if isempty(brk), i1 = idx(end); t_next = t(end);
    else,            i1 = idx(brk); t_next = t(idx(brk+1)); end
    t0 = t(idx(1));  t1 = t(i1);  A = d.edot_c(idx(1));
    win  = t >= t0 & t <= t1;
    plat = t >= t1-1 & t <= t1;
    m.plat_err = A - mean(d.e_rate(plat));
    tt = t(win) - t0;  y = d.e_rate(win);
    i90 = find(y >= 0.9*A, 1);
    if ~isempty(i90), m.tr = tt(i90); end
    m.rms = sqrt(mean((d.e_rate(win) - d.edot_c(win)).^2));
    aft = t >= t1+2 & t < t_next;
    if nnz(aft) > 10
        c = polyfit(t(aft), d.e(aft), 1);  m.drift = c(1);
    end
    m.Vspk = max(abs(d.Vs_til(t >= t0 & t <= t1+2)));
    m.t0 = t0;  m.after = t_next - t1;
end

function overlay(ax, S, names, field, scale, cols)
    hold(ax,'on'); grid(ax,'on');
    for k = 1:numel(names)
        n = names{k};
        if ~isfield(S, n) || isnan(S.(n).m.t0), continue; end
        d = S.(n).d;
        plot(ax, d.t - S.(n).m.t0, scale*d.(field), 'Color', cols{k}, ...
             'LineWidth', 1.3, 'DisplayName', n);
    end
end

function add_ref(ax, S, name, field, scale, c, label)
    if ~isfield(S, name), return; end
    d = S.(name).d;
    plot(ax, d.t - S.(name).m.t0, scale*d.(field), '--', 'Color', c, ...
         'LineWidth', 1, 'DisplayName', label);
end

function save_fig(f, name)
    try
        exportgraphics(f, fullfile('figures', [name '.pdf']), 'ContentType', 'vector');
    catch
        saveas(f, fullfile('figures', [name '.pdf']));
    end
end

function s = pole_str(p)
    if abs(imag(p)) < 1e-9, s = sprintf('%.2f', real(p));
    else,                   s = sprintf('%.2f%+.2fi', real(p), imag(p)); end
end

function rgb = hex2rgb(h)
    rgb = sscanf(h(2:end), '%2x%2x%2x', [1 3]) / 255;
end
