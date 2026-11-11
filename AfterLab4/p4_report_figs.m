%% p4_report_figs.m - Report figures for Part IV (Kalman filter), version 3
% Run from the AfterLab4 folder. Output: figures/report/<name>.pdf (+ .png)
% Self-contained: all plot helpers are local functions at the bottom of this file.
%
%   Figure               Hypothesis / task               Runs
%   p4_noise             Task 1 (Rd), ground vs hover    T4_noise_ground, T4_noise_hover
%   p4_qd_zero           H1: Qd = 0                      T4_test2_Qd_zero (+ baseline P)
%   p4_qd_inf            H2: Qd -> inf                   T4_test3_Qd_inf, T4_test1_Baseline
%   p4_qd_split          H3: rates high vs angles high   T4_test4, T4_test5, T4_test1
%   p4_newdata           Task 3: new-data switch         T4_test6b_NewDataTwice (run of 9 Nov, two cuts)
%   p4_vs_luenberger     Task 3: Kalman vs Luenberger    T4_test7 vs Part III T3_test3_cl
%
% NO smoothing anywhere. Estimation errors are taken against the raw encoder signals.
%
% Signal order (see load_run_p4):
%   enc  = [lambda lambda_dot p p_dot e e_dot]      (e corrected with heli_e_offset)
%   y    = [p p_dot e e_dot lambda_dot]             IMU
%   xhat = [p p_dot e e_dot lambda lambda_dot]      Kalman   (Part III: 5 states, no lambda)
%   u    = [Vs_tilde Vd]
clear; clc; close all;
addpath('utils');

%% ======================= STYLE =======================
S.palette  = 'A';            % 'A' = teal/gold + grey (chosen), 'B' = red/grey
S.width    = 20;             % figure width [cm]
S.font     = 13;             % font size
S.lw       = 1.6;            % clean lines (encoder, flown pitch, covariance)
S.lw_est   = 1.6;            % estimate on top of the encoder
S.lw_ref   = 1.1;            % reference (dashed)
S.lw_thin  = 0.5;            % raw / noisy signals (IMU, Qd -> inf estimate and Vd, p_dot errors)
S.lw_err   = 0.8;            % estimation errors (p_hat - p, e_hat - e) and noise time series
S.lw_cmp   = 1.2;            % clean comparison line drawn on top of a noisy one (Qd -> inf figure)
S.lw_psd   = 1.0;            % noise spectrum
S.axis_lw  = 0.6;            % axis line width
S.grid_col = [0.90 0.90 0.90];
% Figure heights: height = ratio * width. Panel heights are relative (e.g. [3 2] = top 60 %).
S.ratio.noise   = 0.36;   S.panels.noise   = [1 1 1.4];   % widths of: ground | hover | PSD
S.ratio.qd_zero = 0.55;   S.panels.qd_zero = [3 2];
S.ratio.qd_inf  = 0.55;   S.panels.qd_inf  = [1 1 1];
S.ratio.split   = 0.55;   S.panels.split   = [1 1 1];
S.ratio.newdata = 0.55;   S.panels.newdata = [3 2];
S.ratio.luen    = 0.55;   S.panels.luen    = [1 1 1];
S.outdir   = fullfile('figures', 'report');
S.formats  = {'pdf', 'png'};

% Colours by ROLE, so every figure uses them the same way:
%   enc   true signal (encoder)           est   Kalman estimate on top of enc
%   raw   raw IMU measurement (background)
%   base  comparison case (baseline, Luenberger, ground)
%   main  the case the figure is about    third a third case
%   shade new-data disconnected           ref   reference (dashed)
switch S.palette
    case 'A'
        C.enc  = '#004f46';   C.est  = '#d6b43e';   C.raw   = '#d9d9d9';
        C.base = '#8c8c8c';   C.main = '#004f46';   C.third = '#d6b43e';
        C.shade = '#feecd0';
    case 'B'
        C.enc  = '#4d4d4d';   C.est  = '#b2182b';   C.raw   = '#e0e0e0';
        C.base = '#4d4d4d';   C.main = '#b2182b';   C.third = '#ef8a62';
        C.shade = '#fddbc7';
end
C.ref = '#000000';

deg = @rad2deg;
win = @(d, w) d.t >= w(1) & d.t <= w(2);

%% ======================= DATA =======================
Gnd  = load_run_p4('T4_noise_ground');     Hov  = load_run_p4('T4_noise_hover');
Base = load_run_p4('T4_test1_Baseline');   Q0   = load_run_p4('T4_test2_Qd_zero');
Qinf = load_run_p4('T4_test3_Qd_inf');     RH   = load_run_p4('T4_test4_RatesHigh');
AH   = load_run_p4('T4_test5_AnglesHigh'); KF   = load_run_p4('T4_test7_VsLuenberger');
VL   = load_run_p4('T4_test8_VanLoan');
SW   = load_run_p4('T4_test6b_NewDataTwice');   % two cuts; 'T4_test6_NewDataSwitch' has one long cut
LU   = load_p3_run('T3_test3_cl');              % Part III, all states, "balansert" poles

%% ======================= NUMBERS FOR THE TEXT =======================
Yg = detrend(Gnd.y(Gnd.new > 0.5, :));
Yh = detrend(Hov.y(Hov.new > 0.5 & win(Hov, [10 40]), :));
names = {'p', 'p_dot', 'e', 'e_dot', 'lambda_dot'};
fprintf('Task 1: measurement variance (rad^2 or rad^2/s^2)\n');
fprintf('%-11s %12s %12s %8s\n', 'meas', 'ground', 'hover', 'ratio');
for i = 1:5
    fprintf('%-11s %12.2e %12.2e %8.0f\n', names{i}, var(Yg(:,i)), var(Yh(:,i)), ...
            var(Yh(:,i))/var(Yg(:,i)));
end

enc_idx = [3 4 5 6 2];   xh_idx = [1 2 3 4 6];
runs = {Base, 'Baseline'; Qinf, 'Qd inf'; RH, 'Rates high'; AH, 'Angles high'; ...
        KF, 'Kalman (test 7)'; VL, 'Van Loan'};
fprintf('\nRMS estimation error vs encoder, t > 5 s [rad, rad/s]\n');
fprintf('%-16s %8s %8s %8s %8s %8s\n', 'run', 'p', 'p_dot', 'e', 'e_dot', 'l_dot');
for k = 1:size(runs, 1)
    d = runs{k,1};  m = d.t > 5;
    fprintf('%-16s %8.3f %8.3f %8.3f %8.3f %8.3f\n', runs{k,2}, ...
            sqrt(mean((d.xhat(m, xh_idx) - d.enc(m, enc_idx)).^2, 1)));
end
m = LU.t > 5;
fprintf('%-16s %8.3f %8.3f %8.3f %8.3f %8.3f\n', 'Luenberger', ...
        sqrt(mean((LU.xhat(m, 1:5) - LU.enc(m, enc_idx)).^2, 1)));

fprintf('\nstd(Vd) per segment [V]       hover 4-8 s   pitch down 13-18 s\n');
for k = 1:2
    d = {Base, Qinf};  d = d{k};  nm = {'Baseline', 'Qd inf'};
    fprintf('%-28s %8.3f %14.3f\n', nm{k}, std(d.u(win(d,[4 8]),2)), std(d.u(win(d,[13 18]),2)));
end

%% ======================= FIGURE 1: measurement noise, ground vs hover =======================
% One row: 1 s of the IMU elevation on the ground | the same in hover | power spectral density.
% The two time panels have their OWN y-axes (hover noise is about 100x larger in amplitude).
% Mean removed from the time signals (say so in the caption).
w_zoom = [22 23];   w_all = [10 40];
figure('Color', 'w');
wd = S.panels.noise;   cw = round(10*wd);           % column widths in tiles
tl = tiledlayout(1, sum(cw), 'TileSpacing', 'compact', 'Padding', 'compact');
ax = gobjects(1, 3);   col = 1;
for k = 1:3
    ax(k) = nexttile(tl, col, [1 cw(k)]);   hold(ax(k), 'on');   col = col + cw(k);
end
cases = {Gnd, C.base, 'On the ground', [-0.4 0.4]; Hov, C.main, 'Hover', [-25 30]};
for k = 1:2
    d  = cases{k,1};
    mz = win(d, w_zoom);   ma = win(d, w_all);
    plot(ax(k), d.t(mz) - w_zoom(1), deg(d.y(mz,3) - mean(d.y(ma,3))), '-', ...
         'Color', cases{k,2}, 'LineWidth', S.lw_err);
    title(ax(k), cases{k,3});
    xlim(ax(k), [0 1]);   ylim(ax(k), cases{k,4});   xlabel(ax(k), 'time (s)');
end
ylabel(ax(1), 'IMU $e$ (deg)');
for k = [2 1]                                   % hover first in the legend
    d = cases{k,1};
    [f, Pxx] = psd_avg(deg(d.y(win(d, w_all),3)), 500, 2048);
    plot(ax(3), f, Pxx, '-', 'Color', cases{k,2}, 'LineWidth', S.lw_psd, 'DisplayName', cases{k,3});
    if k == 2, [~, ip] = max(Pxx(6:end)); fprintf('\nHover noise in e: peak at %.0f Hz\n', f(ip + 5)); end
end
set(ax(3), 'YScale', 'log', 'YTick', 10.^(-6:2:4));   xlim(ax(3), [0 250]);   ylim(ax(3), [1e-7 1e4]);   % headroom for the legend
xlabel(ax(3), 'frequency (Hz)');   ylabel(ax(3), 'PSD (deg$^2$/Hz)');
p4_legend(ax(3), 'northeast', 1, S);
p4_finish(ax, S, 'p4_noise', S.ratio.noise, false);

%% ======================= FIGURE 2: H1, Qd = 0 =======================
% The controller flies on the estimate. With Qd = 0 the estimate stops following
% the IMU, so the controller tracks its own estimate while the real pitch diverges.
ax = p4_fig(2, 1, S.panels.qd_zero);
plot(ax(1), Q0.t, deg(Q0.y(:,1)),    '-',  'Color', C.raw, 'LineWidth', S.lw_thin, 'DisplayName', 'IMU measurement');
plot(ax(1), Q0.t, deg(Q0.enc(:,3)),  '-',  'Color', C.enc, 'LineWidth', S.lw,      'DisplayName', 'Encoder (true pitch)');
plot(ax(1), Q0.t, deg(Q0.xhat(:,1)), '-',  'Color', C.est, 'LineWidth', S.lw_est,  'DisplayName', 'Estimate $\hat{p}$ (fed to controller)');
plot(ax(1), Q0.t, deg(Q0.ref(:,1)),  '--', 'Color', C.ref, 'LineWidth', S.lw_ref,  'DisplayName', 'Reference $p_c$');
plot(ax(2), Base.t, Base.Pdiag(:,1), '-', 'Color', C.base,  'LineWidth', S.lw, 'DisplayName', '$\hat{P}_{pp}$, baseline');
plot(ax(2), Q0.t,   Q0.Pdiag(:,1),   '-', 'Color', C.main,  'LineWidth', S.lw, 'DisplayName', '$\hat{P}_{pp}$, $Q_d = 0$');
plot(ax(2), Q0.t,   Q0.Pdiag(:,2),   '-', 'Color', C.third, 'LineWidth', S.lw, 'DisplayName', '$\hat{P}_{\dot{p}\dot{p}}$, $Q_d = 0$');
set(ax(2), 'YScale', 'log', 'YTick', 10.^(-9:2:-1));
ylim(ax(1), [-60 120]);   ylim(ax(2), [1e-9 1e-1]);   xlim(ax(2), [0 19]);
ylabel(ax(1), 'pitch $p$ (deg)');   ylabel(ax(2), 'diag$(\hat{P})$');   xlabel(ax(2), 'time $t$ (s)');
p4_legend(ax(1), 'northwest', 2, S);
p4_legend(ax(2), 'northeast', 3, S);
p4_finish(ax, S, 'p4_qd_zero', S.ratio.qd_zero, true);

%% ======================= FIGURE 3: H2, Qd -> infinity =======================
% Over the two pitch steps: the pitch flown is almost the same, but the estimate
% equals the noisy IMU and the noise goes straight into Vd. Noisy run drawn first.
ax = p4_fig(3, 1, S.panels.qd_inf);
plot(ax(1), Base.t, deg(Base.enc(:,3)), '-',  'Color', C.base, 'LineWidth', S.lw,     'DisplayName', 'Baseline');
plot(ax(1), Qinf.t, deg(Qinf.enc(:,3)), '-',  'Color', C.main, 'LineWidth', S.lw,     'DisplayName', '$Q_d \to \infty$');
plot(ax(1), Base.t, deg(Base.ref(:,1)), '--', 'Color', C.ref,  'LineWidth', S.lw_ref, 'DisplayName', 'Reference $p_c$');
plot(ax(2), Qinf.t, deg(Qinf.xhat(:,1)), '-', 'Color', C.main, 'LineWidth', S.lw_thin);
plot(ax(2), Base.t, deg(Base.xhat(:,1)), '-', 'Color', C.base, 'LineWidth', S.lw_cmp);
plot(ax(3), Qinf.t, Qinf.u(:,2), '-', 'Color', C.main, 'LineWidth', S.lw_thin);
plot(ax(3), Base.t, Base.u(:,2), '-', 'Color', C.base, 'LineWidth', S.lw_cmp);
ylim(ax(1), [-28 22]);   ylim(ax(2), [-50 25]);   xlim(ax(3), [7 21]);
ylabel(ax(1), 'pitch $p$ (deg)');   ylabel(ax(2), 'estimate $\hat{p}$ (deg)');
ylabel(ax(3), '$V_d$ (V)');         xlabel(ax(3), 'time $t$ (s)');
p4_legend(ax(1), 'northeast', 3, S);
p4_finish(ax, S, 'p4_qd_inf', S.ratio.qd_inf, true);

%% ======================= FIGURE 4: H3, high q on rates vs on angles =======================
% Top: the pitch that was actually flown. Below: estimate minus raw encoder.
ax = p4_fig(3, 1, S.panels.split);
plot(ax(1), Base.t, deg(Base.enc(:,3)), '-',  'Color', C.base,  'LineWidth', S.lw,     'DisplayName', 'Baseline');
plot(ax(1), RH.t,   deg(RH.enc(:,3)),   '-',  'Color', C.main,  'LineWidth', S.lw,     'DisplayName', 'Rates high');
plot(ax(1), AH.t,   deg(AH.enc(:,3)),   '-',  'Color', C.third, 'LineWidth', S.lw,     'DisplayName', 'Angles high');
plot(ax(1), Base.t, deg(Base.ref(:,1)), '--', 'Color', C.ref,   'LineWidth', S.lw_ref, 'DisplayName', 'Reference $p_c$');
plot(ax(2), AH.t,   deg(AH.xhat(:,1)   - AH.enc(:,3)),   '-', 'Color', C.third, 'LineWidth', S.lw_thin);
plot(ax(2), RH.t,   deg(RH.xhat(:,1)   - RH.enc(:,3)),   '-', 'Color', C.main,  'LineWidth', S.lw_err);
plot(ax(2), Base.t, deg(Base.xhat(:,1) - Base.enc(:,3)), '-', 'Color', C.base,  'LineWidth', S.lw_err);
plot(ax(3), RH.t,   deg(RH.xhat(:,2)   - RH.enc(:,4)),   '-', 'Color', C.main,  'LineWidth', S.lw_thin);
plot(ax(3), AH.t,   deg(AH.xhat(:,2)   - AH.enc(:,4)),   '-', 'Color', C.third, 'LineWidth', S.lw_thin);
plot(ax(3), Base.t, deg(Base.xhat(:,2) - Base.enc(:,4)), '-', 'Color', C.base,  'LineWidth', S.lw_thin);
ylim(ax(1), [-35 32]);   ylim(ax(2), [-16 16]);   ylim(ax(3), [-32 40]);   xlim(ax(3), [7 21]);
ylabel(ax(1), 'pitch $p$ (deg)');
ylabel(ax(2), '$\hat{p} - p$ (deg)');
ylabel(ax(3), '$\hat{\dot{p}} - \dot{p}$ (deg/s)');
xlabel(ax(3), 'time $t$ (s)');
p4_legend(ax(1), 'north', 4, S);
p4_finish(ax, S, 'p4_qd_split', S.ratio.split, true);

%% ======================= FIGURE 5: new-data switch =======================
% The cuts are found from the logged new-data signal: every stretch longer than
% 0.1 s without new data (the IMU itself never skips more than a few samples).
isnew = SW.new(:)' > 0.5;
dz    = diff([1, isnew, 1]);
i0    = find(dz == -1);                      % first sample of each stretch without new data
i1    = find(dz == 1) - 1;                   % last sample of each stretch
keep  = (i1 - i0) > 50;
t_cut = [SW.t(i0(keep)), SW.t(i1(keep))];    % one row per cut: [start stop]
fprintf('\nNew-data disconnected:\n');   fprintf('  %.2f s to %.2f s\n', t_cut');

yl_p = [-22 58];   yl_P = [5e-5 5];
ax = p4_fig(2, 1, S.panels.newdata);
for k = 1:size(t_cut, 1)
    hp = patch('Parent', ax(1), 'XData', t_cut(k, [1 2 2 1]), 'YData', yl_p([1 1 2 2]), ...
               'FaceColor', C.shade, 'EdgeColor', 'none', 'HandleVisibility', 'off');
    patch('Parent', ax(2), 'XData', t_cut(k, [1 2 2 1]), 'YData', yl_P([1 1 2 2]), ...
          'FaceColor', C.shade, 'EdgeColor', 'none', 'HandleVisibility', 'off');
end
plot(ax(1), SW.t, deg(SW.ref(:,1)),  '--', 'Color', C.ref, 'LineWidth', S.lw_ref, 'DisplayName', 'Reference $p_c$');
plot(ax(1), SW.t, deg(SW.enc(:,3)),  '-',  'Color', C.enc, 'LineWidth', S.lw,     'DisplayName', 'Encoder');
plot(ax(1), SW.t, deg(SW.xhat(:,1)), '-',  'Color', C.est, 'LineWidth', S.lw_est, 'DisplayName', 'Estimate $\hat{p}$');
set(hp, 'HandleVisibility', 'on', 'DisplayName', 'New-data disconnected');
plot(ax(2), SW.t, SW.Pdiag(:,1), '-', 'Color', C.base,  'LineWidth', S.lw, 'DisplayName', '$\hat{P}_{pp}$');
plot(ax(2), SW.t, SW.Pdiag(:,2), '-', 'Color', C.main,  'LineWidth', S.lw, 'DisplayName', '$\hat{P}_{\dot{p}\dot{p}}$');
plot(ax(2), SW.t, SW.Pdiag(:,6), '-', 'Color', C.third, 'LineWidth', S.lw, 'DisplayName', '$\hat{P}_{\dot{\lambda}\dot{\lambda}}$');
set(ax(2), 'YScale', 'log', 'YTick', 10.^(-4:0));
ylim(ax(1), yl_p);   ylim(ax(2), yl_P);   xlim(ax(2), [0.5 16]);
ylabel(ax(1), 'pitch $p$ (deg)');   ylabel(ax(2), 'diag$(\hat{P})$');   xlabel(ax(2), 'time $t$ (s)');
p4_legend(ax(1), 'northeast', 2, S);
p4_legend(ax(2), 'northeast', 3, S);
p4_finish(ax, S, 'p4_newdata', S.ratio.newdata, true);

%% ======================= FIGURE 6: Kalman vs Luenberger, full 45 s profile =======================
% Same reference profile and controller in Part III and Part IV.
% Kalman is drawn first (behind) because it is the noisier of the two.
ax = p4_fig(3, 1, S.panels.luen);
plot(ax(1), KF.t, deg(KF.ref(:,1)), '--', 'Color', C.ref,  'LineWidth', S.lw_ref, 'DisplayName', 'Reference $p_c$');
plot(ax(1), KF.t, deg(KF.enc(:,3)), '-',  'Color', C.main, 'LineWidth', S.lw,     'DisplayName', 'Kalman, baseline $Q_d$');
plot(ax(1), LU.t, deg(LU.enc(:,3)), '-',  'Color', C.base, 'LineWidth', S.lw,     'DisplayName', 'Luenberger (Part III)');
plot(ax(2), KF.t, deg(KF.xhat(:,1) - KF.enc(:,3)), '-', 'Color', C.main, 'LineWidth', S.lw_err);
plot(ax(2), LU.t, deg(LU.xhat(:,1) - LU.enc(:,3)), '-', 'Color', C.base, 'LineWidth', S.lw_err);
plot(ax(3), KF.t, deg(KF.xhat(:,3) - KF.enc(:,5)), '-', 'Color', C.main, 'LineWidth', S.lw_err);
plot(ax(3), LU.t, deg(LU.xhat(:,3) - LU.enc(:,5)), '-', 'Color', C.base, 'LineWidth', S.lw_err);
ylim(ax(1), [-28 30]);   ylim(ax(2), [-2.5 2.5]);   ylim(ax(3), [-6 8]);   xlim(ax(3), [2 45]);
ylabel(ax(1), 'pitch $p$ (deg)');
ylabel(ax(2), '$\hat{p} - p$ (deg)');
ylabel(ax(3), '$\hat{e} - e$ (deg)');
xlabel(ax(3), 'time $t$ (s)');
p4_legend(ax(1), 'north', 3, S);
p4_finish(ax, S, 'p4_vs_luenberger', S.ratio.luen, true);

%% ======================= LOCAL FUNCTIONS =======================
function ax = p4_fig(rows, cols, heights)
% New white figure. rows x 1 stacked panels with relative heights, or 1 x cols side by side.
    figure('Color', 'w');
    if cols > 1
        tl = tiledlayout(1, cols, 'TileSpacing', 'compact', 'Padding', 'compact');
        n  = cols;   span = ones(1, cols);
    else
        tl = tiledlayout(sum(heights), 1, 'TileSpacing', 'compact', 'Padding', 'compact');
        n  = rows;   span = heights;
    end
    ax = gobjects(1, n);
    for k = 1:n
        if cols > 1, ax(k) = nexttile(tl); else, ax(k) = nexttile(tl, [span(k) 1]); end
        hold(ax(k), 'on');
    end
end

function p4_legend(ax, loc, ncol, S)
% Legend inside the axes, no box.
    lg = legend(ax, 'show');
    set(lg, 'Location', loc, 'NumColumns', ncol, 'Box', 'off');
end

function p4_finish(ax, S, fname, ratio, share_x)
% Common look + export. share_x = true: stacked panels share the x-axis,
% tick numbers only on the bottom panel.
    hfig = ancestor(ax(1), 'figure');
    set(hfig, 'Units', 'centimeters', 'Position', [3 3 S.width ratio*S.width]);
    set(ax, 'Box', 'off', 'TickDir', 'in', 'LineWidth', S.axis_lw, 'Layer', 'top', ...
            'XGrid', 'on', 'YGrid', 'on', 'GridColor', S.grid_col, 'GridAlpha', 1, ...
            'XMinorGrid', 'off', 'YMinorGrid', 'off', 'MinorGridLineStyle', 'none');
    set(findall(hfig, '-property', 'FontSize'), 'FontSize', S.font);
    set(findall(hfig, '-property', 'Interpreter'), 'Interpreter', 'latex');
    set(findall(hfig, '-property', 'TickLabelInterpreter'), 'TickLabelInterpreter', 'latex');
    if share_x && numel(ax) > 1
        linkaxes(ax, 'x');
        drawnow
        for k = 1:numel(ax) - 1
            ax(k).XTick      = ax(end).XTick;
            ax(k).XTickLabel = [];
        end
    end
    drawnow
    pos = get(hfig, 'Position');
    set(hfig, 'PaperPositionMode', 'Auto', 'PaperUnits', 'centimeters', 'PaperSize', [pos(3), pos(4)]);
    if ~exist(S.outdir, 'dir'), mkdir(S.outdir); end
    f = fullfile(S.outdir, fname);
    if any(strcmp(S.formats, 'pdf')), print(hfig, f, '-dpdf', '-vector', '-fillpage'); end
    if any(strcmp(S.formats, 'png')), print(hfig, f, '-dpng', '-r300'); end
    fprintf('Saved %s\n', f);
end

function [f, Pxx] = psd_avg(x, fs, N)
% Averaged periodogram (Hann window, 50 % overlap), one-sided, in unit^2/Hz.
% Written out with fft so that no toolbox is needed.
    x    = detrend(x(:));
    wdw  = 0.5 - 0.5*cos(2*pi*(0:N-1)'/N);
    step = N/2;
    K    = floor((numel(x) - N)/step) + 1;
    Pxx  = zeros(N/2 + 1, 1);
    for k = 1:K
        X   = fft(x((k-1)*step + (1:N)) .* wdw);
        Pxx = Pxx + abs(X(1:N/2 + 1)).^2;
    end
    Pxx = Pxx / (K*fs*sum(wdw.^2));
    Pxx(2:end-1) = 2*Pxx(2:end-1);
    f = (0:N/2)' * fs/N;
end

function d = load_p3_run(tag)
% Part III run (same Mux order as Part IV, but xhat is 5 wide and there is no Pdiag):
%   enc(6) | gyro(3) | acc(3) | new(1) | y(5) | xhat(5) | ref(2) | u(2)
    S = load(fullfile('..', 'AfterLab3', 'data', ['p3_' tag '.mat']));
    f = fieldnames(S);
    D = S.(f{1})';
    d.t    = D(:,1);
    d.enc  = D(:,2:7);
    d.new  = D(:,14);
    d.y    = D(:,15:19);
    d.xhat = D(:,20:24);
    d.ref  = D(:,25:26);
    d.u    = D(:,27:28);
    d.enc(:,5) = d.enc(:,5) - heli_e_offset();   % same elevation offset as load_run_p4
end
