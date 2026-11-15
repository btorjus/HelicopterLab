%% p3_report_figs.m - Report figures for Part III (Luenberger observer)
% Run from the AfterLab3 folder. Output: figures/report/<name>.pdf (+ .png)
% Colours and look from AfterLab1 (Task_2.m): Zissou palette, dashed black
% reference, no grid, no legend box. Self-contained: helpers at the bottom.
%
%   Figure       Content                                        Runs
%   p3_ref       reference profile (test plan), black/white, very low   test 3 (any run: same profile)
%   p3_sine      pitch sine 30-42 s, All vs Min, slow/bal/fast  tests 2,3,1 (All) and 5,6 (Min)
%   p3_drift     whole profile, all states: pitch + p_hat - p   tests 2,3,1
%   p3_vd        V_d in hover, All vs Min side by side          tests 7,1,3,2 (All) and 4,6,5 (Min)
%
%   Test numbers (p3_observer.m):
%     1 All fast   2 All slow   3 All balanced   7 All very fast
%     4 Min fast   5 Min slow   6 Min balanced   8 Min very fast (never left the ground, not plotted)
clear; clc; close all;
addpath('utils');

%% ======================= STYLE =======================
S.width   = 20;              % figure width [cm]
S.font    = 13;              % font size
S.lw      = 1.2;             % main lines (as in AfterLab1)
S.lw_est  = 1.2;             % estimate drawn on top of the encoder
S.lw_ref  = 1.2;             % reference (dashed, as in AfterLab1)
S.lw_thin = 0.6;             % raw / noisy signals
S.lw_err  = 0.9;             % estimation error of the balanced run (p3_drift)
S.axis_lw = 0.6;
S.grid    = false;           % AfterLab1 has no grid
S.outdir  = fullfile('figures', 'report');
S.formats = {'pdf'};

% Figure heights: height = ratio * width. Panel heights are relative (whole numbers).
S.ratio.ref   = 0.22;   S.font_ref = 10;   % small visual aid in the test plan
S.ratio.sine  = 0.85;
S.ratio.drift = 0.55;   S.panels.drift = [1 1];
S.ratio.vd    = 0.50;

% Colours (AfterLab1). One colour per pole set in every Part III figure.
C.slow     = '#3B9AB2';      % deep teal
C.balanced = '#F21A00';      % deep red
C.fast     = '#E1AF00';      % mustard / ochre
C.vfast    = '#3E9B5F';      % green (Marginally stable in the Part I figure)
C.ref      = '#000000';      % black, dashed reference (as in Part II)
C.raw      = '#D9D9D9';      % raw IMU measurement (background)
% Sine figure (colour = signal, not pole set):
C.enc      = C.slow;         % encoder
C.est      = C.balanced;     % estimate

deg = @rad2deg;
win = @(d, w) d.t >= w(1) & d.t <= w(2);

%% ======================= DATA =======================
D = cell(1, 7);
for n = 1:7, D{n} = load_p3_run(n); end
name = {'All, fast', 'All, slow', 'All, balanced', 'Min, fast', ...
        'Min, slow', 'Min, balanced', 'All, very fast'};

%% ======================= FIGURE 0: reference profile (test plan) =======================
% Black and white, very low. Thin grey lines at the segment boundaries,
% labels above the main segments. All runs use the same profile, so test 3 is used.
d    = D{3};   m = d.t <= 45;
% label, x position, alignment ('take-off' and 'hover' are pushed apart: the segments are narrow)
segs = {'take-off', 3.8, 'right'; 'hover', 4.3, 'left'; 'pitch steps', 13, 'center'; ...
        'climb, descent', 24, 'center'; 'pitch sine', 36, 'center'};
ax   = p3_fig(2, [1 1]);
yl = {[-20 14], [-8 11]};                        % y-limits of the two panels
for k = 1:2
    for x = [1 4 8 18 21 27 30 42]                % segment boundaries (plain lines: works in older MATLAB)
        plot(ax(k), [x x], yl{k}, '-', 'Color', [0.75 0.75 0.75], 'LineWidth', 0.5);
    end
end
plot(ax(1), d.t(m), deg(d.ref(m,1)), '-', 'Color', 'k', 'LineWidth', S.lw_ref);
plot(ax(2), d.t(m), deg(d.ref(m,2)), '-', 'Color', 'k', 'LineWidth', S.lw_ref);
for k = 1:size(segs, 1)
    text(ax(1), segs{k,2}, 15, segs{k,1}, ...
         'HorizontalAlignment', segs{k,3}, 'VerticalAlignment', 'bottom');
end
ylim(ax(1), yl{1});   yticks(ax(1), [-17.2 0 8.6]);    % ticks at the actual levels
ylim(ax(2), yl{2});   yticks(ax(2), [-5.7 0 8.6]);
xlim(ax(2), [0 45]);
% Horizontal y-labels on one line; the tiled layout makes the axes narrower to fit them
ylabel(ax(1), '$p_c$ (deg)',           'Rotation', 0, 'HorizontalAlignment', 'right', 'VerticalAlignment', 'middle');
ylabel(ax(2), '$\dot{e}_c$ (deg/s)',  'Rotation', 0, 'HorizontalAlignment', 'right', 'VerticalAlignment', 'middle');
xlabel(ax(2), 'time $t$ (s)');
set(findall(ax(1), 'Type', 'text'), 'Clipping', 'off');
Sr = S;   Sr.font = S.font_ref;
p3_finish(ax, Sr, 'p3_ref', S.ratio.ref, true);
% Re-export the PDF cropped to the content (removes the white space around this low figure)
exportgraphics(ancestor(ax(1), 'figure'), fullfile(S.outdir, 'p3_ref.pdf'), 'ContentType', 'vector');

%% ======================= FIGURE 1: pitch sine, All vs Min =======================
% Rows: slow, balanced, fast poles. Columns: all states, minimum states.
% Min, fast is left out (estimate far off scale); its legend sits in that slot.
w    = [30 42];
grid_runs = [2 5; 3 6; 1 0];               % 0 = empty slot (legend)
figure('Color', 'w');
tl = tiledlayout(3, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
ax = gobjects(1, 5);   k = 0;
for r = 1:3
    for c = 1:2
        n = grid_runs(r, c);
        if n == 0, continue; end
        k = k + 1;
        ax(k) = nexttile(tl, (r-1)*2 + c);   hold(ax(k), 'on');
        d = D{n};   m = win(d, w);
        plot(ax(k), d.t(m), deg(d.y(m,1)),    '-',  'Color', C.raw, 'LineWidth', S.lw_thin, 'DisplayName', 'IMU measurement');
        plot(ax(k), d.t(m), deg(d.ref(m,1)),  '--', 'Color', C.ref, 'LineWidth', S.lw_ref,  'DisplayName', 'Reference $p_c$');
        plot(ax(k), d.t(m), deg(d.enc(m,3)),  '-',  'Color', C.enc, 'LineWidth', S.lw,      'DisplayName', 'Encoder $p$');
        plot(ax(k), d.t(m), deg(d.xhat(m,1)), '-',  'Color', C.est, 'LineWidth', S.lw_est,  'DisplayName', 'Estimate $\hat{p}$');
        title(ax(k), name{n});
        if c == 1, ylabel(ax(k), 'pitch (deg)'); else, ax(k).YTickLabel = []; end
        if r == 3 || (r == 2 && c == 2), xlabel(ax(k), 'time $t$ (s)'); else, ax(k).XTickLabel = []; end
    end
end
linkaxes(ax, 'xy');   xlim(ax(1), w);   ylim(ax(1), [-50 45]);
lg = legend(ax(1), 'show');   lg.Box = 'off';
lg.Layout.Tile = 6;                         % empty slot bottom right
p3_finish(ax, S, 'p3_sine', S.ratio.sine);

%% ======================= FIGURE 2: whole profile, all states =======================
% Top: pitch flown with the slow and the balanced observer.
% Bottom: estimation error p_hat - p for slow, balanced and fast (noisiest at the back).
ax = p3_fig(2, S.panels.drift);
plot(ax(1), D{3}.t, deg(D{3}.ref(:,1)), '--', 'Color', C.ref,      'LineWidth', S.lw_ref, 'DisplayName', 'Reference $p_c$');
plot(ax(1), D{3}.t, deg(D{3}.enc(:,3)), '-',  'Color', C.balanced, 'LineWidth', S.lw,     'DisplayName', name{3});
plot(ax(1), D{2}.t, deg(D{2}.enc(:,3)), '-',  'Color', C.slow,     'LineWidth', S.lw,     'DisplayName', name{2});
h3 = plot(ax(2), D{1}.t, deg(D{1}.xhat(:,1) - D{1}.enc(:,3)), '-', 'Color', C.fast,     'LineWidth', S.lw_thin, 'DisplayName', name{1});
h2 = plot(ax(2), D{3}.t, deg(D{3}.xhat(:,1) - D{3}.enc(:,3)), '-', 'Color', C.balanced, 'LineWidth', S.lw_err,  'DisplayName', name{3});
h1 = plot(ax(2), D{2}.t, deg(D{2}.xhat(:,1) - D{2}.enc(:,3)), '-', 'Color', C.slow,     'LineWidth', S.lw,      'DisplayName', name{2});
ylim(ax(1), [-30 40]);   ylim(ax(2), [-25 5]);   xlim(ax(2), [2 45]);
ylabel(ax(1), 'pitch $p$ (deg)');   ylabel(ax(2), '$\hat{p} - p$ (deg)');   xlabel(ax(2), 'time $t$ (s)');
lg = legend(ax(1), 'show');   set(lg, 'Location', 'northwest', 'NumColumns', 3, 'Box', 'off');
legend(ax(2), [h1 h2 h3], 'Location', 'southwest', 'NumColumns', 3, 'Box', 'off');
p3_finish(ax, S, 'p3_drift', S.ratio.drift, true);

%% ======================= FIGURE 3: V_d in hover, All vs Min =======================
% Same y-axis in both panels. Std over the window in the legend (below the plots,
% so it does not cover the Min, fast curve). Window ends just before the pitch step at 8 s.
w = [5 7.95];
runs = {[7 1 3 2], {'very fast', 'fast', 'balanced', 'slow'}, {C.vfast, C.fast, C.balanced, C.slow}, 'All states, $C = I_5$';
        [4 6 5],   {'fast', 'balanced', 'slow'},              {C.fast, C.balanced, C.slow},          'Minimum, $y = [e,\ \dot{\lambda}]$'};
figure('Color', 'w');
tl = tiledlayout(1, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
ax = gobjects(1, 2);
fprintf('std(V_d), %.2f-%.2f s:\n', w);
for k = 1:2
    ax(k) = nexttile(tl);   hold(ax(k), 'on');
    nn = runs{k,1};   h = gobjects(1, numel(nn));
    for j = 1:numel(nn)                       % noisiest first = at the back
        d = D{nn(j)};   m = win(d, w);   s = std(d.u(m,2));
        if any(strcmp(runs{k,2}{j}, {'slow', 'balanced'})), lw = S.lw; else, lw = S.lw_thin; end
        h(j) = plot(ax(k), d.t(m), d.u(m,2), '-', 'Color', runs{k,3}{j}, 'LineWidth', lw, ...
                    'DisplayName', sprintf('%s: %.2f V', runs{k,2}{j}, s));
        fprintf('  %-15s %.3f V\n', name{nn(j)}, s);
    end
    title(ax(k), runs{k,4});
    xlabel(ax(k), 'time $t$ (s)');
    lg = legend(ax(k), fliplr(h), 'Location', 'southoutside', 'NumColumns', 2, 'Box', 'off');
    title(lg, 'std of $V_d$');
end
linkaxes(ax, 'xy');   xlim(ax(1), w);   ylim(ax(1), [-3 3]);
ylabel(ax(1), '$V_d$ (V)');   ax(2).YTickLabel = [];
p3_finish(ax, S, 'p3_vd', S.ratio.vd);

%% ======================= LOCAL FUNCTIONS =======================
function ax = p3_fig(rows, heights)
% New white figure with rows stacked panels, relative heights (whole numbers).
    figure('Color', 'w');
    tl = tiledlayout(sum(heights), 1, 'TileSpacing', 'compact', 'Padding', 'compact');
    ax = gobjects(1, rows);
    for k = 1:rows
        ax(k) = nexttile(tl, [heights(k) 1]);   hold(ax(k), 'on');
    end
end

function p3_finish(ax, S, fname, ratio, share_x)
% Common look (AfterLab1 template) + export.
    if nargin < 5, share_x = false; end
    hfig = ancestor(ax(1), 'figure');
    set(hfig, 'Units', 'centimeters', 'Position', [3 3 S.width ratio*S.width]);
    set(ax, 'Box', 'off', 'TickDir', 'in', 'LineWidth', S.axis_lw);
    if S.grid, grid(ax, 'on'); else, grid(ax, 'off'); end
    set(findall(hfig, '-property', 'FontSize'), 'FontSize', S.font);
    set(findall(hfig, '-property', 'Interpreter'), 'Interpreter', 'latex');
    set(findall(hfig, '-property', 'TickLabelInterpreter'), 'TickLabelInterpreter', 'latex');
    if share_x && numel(ax) > 1
        xl = xlim(ax(end));            % time window set on the bottom panel
        linkaxes(ax, 'x');             % (linkaxes would otherwise take the limits of the top panel)
        xlim(ax(end), xl);
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

function d = load_p3_run(n)
% Part III closed-loop run n (data/p3_T3_test<n>_cl.mat). Mux order (load_p3.m):
%   enc(6) | gyro(3) | acc(3) | new(1) | y(5) | xhat(5) | ref(2) | u(2)
%   enc  = [lambda lambda_dot p p_dot e e_dot]   y, xhat = [p p_dot e e_dot lambda_dot]
    S = load(fullfile('data', sprintf('p3_T3_test%d_cl.mat', n)));
    f = fieldnames(S);
    D = S.(f{1})';
    d.t    = D(:,1);
    d.enc  = D(:,2:7);
    d.new  = D(:,14);
    d.y    = D(:,15:19);
    d.xhat = D(:,20:24);
    d.ref  = D(:,25:26);
    d.u    = D(:,27:28);
    d.enc(:,5) = d.enc(:,5) - heli_e_offset();   % elevation encoder offset (Part I)
end
