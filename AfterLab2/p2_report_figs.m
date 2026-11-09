%% p2_report_figs.m — Report figures for Part II (LQR and LQR with integral action)
% Run from the AfterLab2 folder. Output: figures/report/<name>.pdf (+ .png)
%
%   STYLE                    -> everything about the look, change it here
%   new_report_fig(n, h)     -> figure with n stacked panels (h = relative heights)
%   report_line(...)         -> one line, kind = 'meas' | 'meas2' | 'model' | 'ref' | 'input'
%   finish_report_fig(...)   -> labels, limits, legend, group template, export
clear; clc; close all;
addpath('utils');
heli_params;                                   % K1, K2

%% ======================= STYLE =======================
S.width       = 20;          % figure width [cm]          (group template: keep fixed)
S.ratio       = 0.55;        % height/width, one panel    (group template)
S.ratio_multi = 0.55;        % height/width, several panels
S.font        = 13;          % font size                  (group template)
S.lw          = 1.5;         % measured lines
S.lw_model    = 1.5;         % model lines (dotted)
S.lw_ref      = 1.5;         % reference lines (dashed)
S.lw_input    = 1.5;         % input voltages
S.axis_lw     = 0.8;         % axis line width
S.tickdir     = 'in';        % 'in' | 'out'
S.grid        = false;       % true | false
S.legend_loc  = 'best';      % 'best', 'southeast', 'northeast', ...
S.legend_cols = 3;           % legend columns
S.outdir      = fullfile('figures', 'report');
S.formats     = {'pdf', 'png'};
S.smooth_elev = 0.3;         % [s] centered moving average on e_dot and Vs~ in Fig. 2 (0 = raw)
                             %     (encoder quantization makes the raw rate signal pure spikes)

% Colours (Zissou palette, light blue replaced by dark maroon for contrast)
C.teal  = '#3B9AB2';   C.red  = '#F21A00';   C.ochre = '#E1AF00';
C.light = '#5B1A18';   C.ref  = '#000000';   C.grey  = '#8A8A85';


%% ======================= DATA =======================
ts  = @(d) d.t - d.t(find(d.pc ~= 0, 1));      % time since pitch step
pc  = 0.3;                                     % pitch step [rad]
deg = @rad2deg;
sm  = @(x) movmean(x, max(1, round(S.smooth_elev/0.002)));   % centered, 0.002 s sample time

Base  = load_run_p2('Baseline_pitch');     IBase = load_run_p2('IBaseline_pitch');
Aggr  = load_run_p2('Aggressive_pitch');   IHigh = load_run_p2('IHigh_pitch');
Slug  = load_run_p2('Sluggish_pitch');     ILow  = load_run_p2('ILow_pitch');
Cheap = load_run_p2('CheapVd_pitch');      INoF  = load_run_p2('IBaselineNoF_pitch');
Prio  = load_run_p2('PitchPrio_pitch');    Damp  = load_run_p2('PitchDamp_pitch');

BaseE = load_run_p2('Baseline_elev');      SlugE = load_run_p2('Sluggish_elev');
AggrE = load_run_p2('Aggressive_elev');    IBasE = load_run_p2('IBaseline_elev');

%% ======================= MODELS =======================
A  = [0 1 0; 0 0 0; 0 0 0];                     % x = [p; p_dot; e_dot]
B  = [0 0; 0 K1; K2 0];
[Q, R] = p2_weights('Baseline');
K  = lqr(A, B, Q, R);

% Pitch, LQR:            p/pc     = K1*k21 / (s^2 + K1*k22*s + K1*k21)
G_pitch = tf(K1*K(2,1), [1, K1*K(2,2), K1*K(2,1)]);
% Elevation rate, LQR:   edot/edc = K2*k13 / (s + K2*k13)
G_elev  = tf(K2*K(1,3), [1, K2*K(1,3)]);

% Pitch with integral action (x = [p; p_dot; e_dot; gamma; zeta], q_gamma = q_zeta = 1):
%   p/pc = K1*(F21*s - k24) / (s^3 + K1*k22*s^2 + K1*k21*s - K1*k24),  F21 = k21 (with F) or 0
Ai = [A zeros(3,2); -1 0 0 0 0; 0 0 -1 0 0];
Bi = [B; zeros(2)];
Ki = lqr(Ai, Bi, blkdiag(Q, eye(2)), R);
den_i = [1, K1*Ki(2,2), K1*Ki(2,1), -K1*Ki(2,4)];
G_iF  = tf(K1*[Ki(2,1), -Ki(2,4)], den_i);
G_i0  = tf(K1*[0,       -Ki(2,4)], den_i);

%% ======================= FIGURE 1: Q/R scaling (pitch + Vd) =======================
tm = 0:0.01:10;
ax = new_report_fig(2, [2 1]);
report_line(ax(1), ts(Base),  deg(Base.p),  C.teal,  'meas',  'Baseline',   S);
report_line(ax(1), ts(Aggr),  deg(Aggr.p),  C.red,   'meas',  'Aggressive', S);
report_line(ax(1), ts(Slug),  deg(Slug.p),  C.ochre, 'meas',  'Sluggish',   S);
report_line(ax(1), ts(Cheap), deg(Cheap.p), C.light, 'meas2', 'CheapVd',    S);
report_line(ax(1), tm, deg(pc*step(G_pitch, tm)), C.teal, 'model', 'Baseline model', S);
report_line(ax(1), [-1 0 0 10], deg([0 0 pc pc]), C.ref, 'ref', 'Reference $p_c$', S);
report_line(ax(2), ts(Base), Base.Vd, C.teal,  'input', '', S);
report_line(ax(2), ts(Aggr), Aggr.Vd, C.red,   'input', '', S);
report_line(ax(2), ts(Slug), Slug.Vd, C.ochre, 'input', '', S);
finish_report_fig(ax, S, 'time since pitch step $t$ (s)', {'pitch $p$ (deg)', '$V_d$ (V)'}, ...
                  [-1 10], {[-1 20], []}, 'p2_pitch_qr');

%% ======================= FIGURE 1b: individual pitch weights (pitch + Vd) =======================
tm = 0:0.01:10;
ax = new_report_fig(2, [2 1]);
report_line(ax(1), ts(Base), deg(Base.p), C.teal, 'meas', 'Baseline',  S);
report_line(ax(1), ts(Prio), deg(Prio.p), C.red,  'meas', 'PitchPrio', S);
report_line(ax(1), ts(Damp), deg(Damp.p), C.ochre,'meas', 'PitchDamp', S);
report_line(ax(1), tm, deg(pc*step(G_pitch, tm)), C.teal, 'model', 'Baseline model', S);
report_line(ax(1), [-1 0 0 10], deg([0 0 pc pc]), C.ref, 'ref', 'Reference $p_c$', S);
report_line(ax(2), ts(Base), Base.Vd, C.teal,  'input', '', S);
report_line(ax(2), ts(Prio), Prio.Vd, C.red,   'input', '', S);
report_line(ax(2), ts(Damp), Damp.Vd, C.ochre, 'input', '', S);
finish_report_fig(ax, S, 'time since pitch step $t$ (s)', {'pitch $p$ (deg)', '$V_d$ (V)'}, ...
                  [-1 10], {[-1 20], []}, 'p2_pitch_weights');

%% ======================= FIGURE 2: elevation rate (e_dot + Vs~), second pulse =======================
% The second pulse starts at t = 25 s (the first overlaps with take-off).
t0 = 25;
w  = BaseE.t >= t0 - 1 & BaseE.t <= t0 + 7;
tw = BaseE.t(w) - t0;
ax = new_report_fig(2, [2 1]);
report_line(ax(1), BaseE.t - t0, deg(sm(BaseE.e_rate)), C.teal,  'meas',  'Baseline',   S);
report_line(ax(1), AggrE.t - t0, deg(sm(AggrE.e_rate)), C.red,   'meas',  'Aggressive', S);
report_line(ax(1), SlugE.t - t0, deg(sm(SlugE.e_rate)), C.ochre, 'meas',  'Sluggish',   S);
report_line(ax(1), IBasE.t - t0, deg(sm(IBasE.e_rate)), C.light, 'meas2', 'IBaseline',  S);
report_line(ax(1), tw, deg(lsim(G_elev, BaseE.edot_c(w)', tw - tw(1))), C.teal, 'model', 'Baseline model', S);
report_line(ax(1), tw, deg(BaseE.edot_c(w)), C.ref, 'ref', 'Reference $\dot{e}_c$', S);
report_line(ax(2), BaseE.t - t0, sm(BaseE.Vs_til), C.teal,  'input', '', S);
report_line(ax(2), AggrE.t - t0, sm(AggrE.Vs_til), C.red,   'input', '', S);
report_line(ax(2), SlugE.t - t0, sm(SlugE.Vs_til), C.ochre, 'input', '', S);
report_line(ax(2), IBasE.t - t0, sm(IBasE.Vs_til), C.light, 'input', '', S);
finish_report_fig(ax, S, 'time since start of pulse $t$ (s)', ...
                  {'elevation rate $\dot{e}$ (deg/s)', '$\tilde{V}_s$ (V)'}, [-0.5 5], {[], []}, 'p2_elev_rate');

%% ======================= FIGURE 3: without vs with integral action (pitch + Vd) =======================
ax = new_report_fig(2, [2 1]);
report_line(ax(1), ts(Base),  deg(Base.p),  C.teal,  'meas', 'LQR Baseline', S);
report_line(ax(1), ts(IBase), deg(IBase.p), C.red,   'meas', 'IBaseline',    S);
report_line(ax(1), ts(IHigh), deg(IHigh.p), C.ochre, 'meas', 'IHigh',        S);
report_line(ax(1), ts(ILow),  deg(ILow.p),  C.light, 'meas', 'ILow',         S);
report_line(ax(1), [-2 0 0 25], deg([0 0 pc pc]), C.ref, 'ref', 'Reference $p_c$', S);
report_line(ax(2), ts(Base),  Base.Vd,  C.teal,  'input', '', S);
report_line(ax(2), ts(IBase), IBase.Vd, C.red,   'input', '', S);
report_line(ax(2), ts(IHigh), IHigh.Vd, C.ochre, 'input', '', S);
report_line(ax(2), ts(ILow),  ILow.Vd,  C.light, 'input', '', S);
finish_report_fig(ax, S, 'time since pitch step $t$ (s)', {'pitch $p$ (deg)', '$V_d$ (V)'}, ...
                  [-2 25], {[-1 23], []}, 'p2_integral');

%% ======================= FIGURE 4: integral action with and without F (pitch + Vd) =======================
tm = 0:0.01:25;
ax = new_report_fig(2, [2 1]);
report_line(ax(1), ts(IBase), deg(IBase.p), C.red,   'meas', 'With $F$', S);
report_line(ax(1), ts(INoF),  deg(INoF.p),  C.light, 'meas', '$F = 0$',  S);
report_line(ax(1), tm, deg(pc*step(G_iF, tm)), C.red,   'model', 'Model, with $F$', S);
report_line(ax(1), tm, deg(pc*step(G_i0, tm)), C.light, 'model', 'Model, $F = 0$',  S);
report_line(ax(1), [-2 0 0 25], deg([0 0 pc pc]), C.ref, 'ref', 'Reference $p_c$', S);
report_line(ax(2), ts(IBase), IBase.Vd, C.red,   'input', '', S);
report_line(ax(2), ts(INoF),  INoF.Vd,  C.light, 'input', '', S);
finish_report_fig(ax, S, 'time since pitch step $t$ (s)', {'pitch $p$ (deg)', '$V_d$ (V)'}, ...
                  [-2 25], {[-1 23], []}, 'p2_feedforward');
