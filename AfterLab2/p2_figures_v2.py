"""
p2_figures_v2.py - Report figures (alternative layout) for Part II (LQR and LQR with integral action).

Run from the AfterLab2 folder:      python p2_figures_v2.py
Needs:                              numpy, scipy, matplotlib
Reads:                              data/p2/HeliRun_<run>.mat and data/p2/p2Run_<run>.mat
Writes:                             figures/report_py/<name>.pdf (+ .png preview)

The figures are made at the true text width of the report, so the font size in the
figure equals the font size on the page. Include them with
    \\includegraphics[width=\\linewidth]{...}
"""
from pathlib import Path

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import scipy.io as sio
from scipy.linalg import solve_continuous_are
from scipy.signal import lsim

# ============================ SETTINGS ============================
TEXTWIDTH_CM = 12.7      # text width of the report. article 11pt without geometry: 12.7 cm.
                         # With \usepackage[margin=2.5cm]{geometry}: 16.0 cm.
FONT_PT      = 9         # labels and legend (report body text is 11 pt)
TICK_PT      = 8
SMOOTH_S     = 0.1       # moving average on e_dot and input voltages [s]; 0 = raw
LW_MEAS, LW_INPUT, LW_MODEL, LW_REF = 1.1, 0.8, 1.0, 0.8

# Okabe-Ito colours (colour-blind safe, print well)
BLUE, ORANGE, GREEN, PURPLE = "#0072B2", "#D55E00", "#009E73", "#CC79A7"
GREY, BLACK = "#555555", "#000000"

HERE    = Path(__file__).resolve().parent
DATADIR = HERE / "data" / "p2"
OUTDIR  = HERE / "figures" / "report_py_v2"

plt.rcParams.update({
    "font.family": "cmr10",              # Computer Modern, same as the LaTeX template
    "mathtext.fontset": "cm",
    "axes.formatter.use_mathtext": True,
    "axes.unicode_minus": False,
    "font.size": FONT_PT, "axes.labelsize": FONT_PT, "legend.fontsize": FONT_PT - 1,
    "xtick.labelsize": TICK_PT, "ytick.labelsize": TICK_PT,
    "axes.linewidth": 0.6, "xtick.major.width": 0.6, "ytick.major.width": 0.6,
    "xtick.major.size": 3, "ytick.major.size": 3,
    "xtick.direction": "out", "ytick.direction": "out",
    "axes.spines.top": False, "axes.spines.right": False,
    "axes.grid": True, "grid.color": "#e3e3e3", "grid.linewidth": 0.4,
    "legend.frameon": False, "legend.handlelength": 1.8, "legend.columnspacing": 1.2,
    "legend.handletextpad": 0.5, "legend.borderaxespad": 0.3,
    "pdf.fonttype": 42, "savefig.dpi": 300,
})

# ============================ MODEL ============================
g, m_c, m_p, l_c, l_h, l_p, Vs0 = 9.81, 1.92, 0.72, 0.46, 0.66, 0.175, 7.3
K_f = -g * (m_c * l_c - 2 * m_p * l_h) / (l_h * Vs0)
K1 = K_f * l_p / (2 * m_p * l_p**2)
K2 = K_f * l_h / (m_c * l_c**2 + 2 * m_p * l_h**2)
A = np.array([[0, 1, 0], [0, 0, 0], [0, 0, 0.0]])          # x = [p, p_dot, e_dot]
B = np.array([[0, 0], [0, K1], [K2, 0]])
Q0 = np.diag([1 / np.deg2rad(30) ** 2, 1.0, 1 / 0.3**2])   # Bryson's rule baseline
R0 = np.diag([1 / 5**2, 1 / 2**2])
DT = 0.002
V_SAT = 5.0                                                # motor voltage limit [V]


def lqr(A, B, Q, R):
    P = solve_continuous_are(A, B, Q, R)
    return np.linalg.solve(R, B.T @ P)


K = lqr(A, B, Q0, R0)                                      # baseline LQR gain
Ai = np.block([[A, np.zeros((3, 2))], [np.array([[-1, 0, 0], [0, 0, -1.0]]), np.zeros((2, 2))]])
Bi = np.vstack([B, np.zeros((2, 2))])
Ki = lqr(Ai, Bi, np.diag([*np.diag(Q0), 1, 1]), R0)        # integral action, q_I = 1


def pitch_model(t, pc=0.3):
    """Baseline LQR: p/pc = K1 k21 / (s^2 + K1 k22 s + K1 k21)."""
    k21, k22 = K[1, 0], K[1, 1]
    _, y, _ = lsim(([K1 * k21], [1, K1 * k22, K1 * k21]), np.full_like(t, pc), t)
    return y


def pitch_model_integral(t, with_F, pc=0.3):
    """q_I = 1: p/pc = K1 (F21 s - k24) / (s^3 + K1 k22 s^2 + K1 k21 s - K1 k24), F21 = k21 or 0."""
    k21, k22, k24 = Ki[1, 0], Ki[1, 1], Ki[1, 3]
    num = [K1 * k21, -K1 * k24] if with_F else [-K1 * k24]
    _, y, _ = lsim((num, [1, K1 * k22, K1 * k21, -K1 * k24]), np.full_like(t, pc), t)
    return y


def elev_model(t, edc):
    """Baseline LQR: e_dot/e_dot_c = K2 k13 / (s + K2 k13)."""
    k13 = K[0, 2]
    _, y, _ = lsim(([K2 * k13], [1, K2 * k13]), edc, t)
    return y


# ============================ DATA ============================
def _mat(path):
    d = sio.loadmat(path)
    return next(v for k, v in d.items() if not k.startswith("__"))


def load(name):
    H, P = _mat(DATADIR / f"HeliRun_{name}.mat"), _mat(DATADIR / f"p2Run_{name}.mat")
    return dict(t=H[0], trav_rate=H[2], p=H[3], e_rate=H[6], pc=P[1], edc=P[2], Vs=P[3], Vd=P[4])


def smooth(x):
    n = max(1, int(round(SMOOTH_S / DT)))
    return x if n == 1 else np.convolve(np.pad(x, n // 2, mode="edge"), np.ones(n) / n, "valid")[: len(x)]


def t_step(r):
    """Time relative to the pitch step."""
    return r["t"] - r["t"][np.argmax(r["pc"] != 0)]


def t_pulse(r, k=2):
    """Time relative to the start of the k-th elevation-rate pulse."""
    rise = np.flatnonzero(np.diff((r["edc"] > 0).astype(int)) == 1) + 1
    return r["t"] - r["t"][rise[k - 1]]


# ============================ FIGURE HELPERS ============================
deg = np.rad2deg
CM = 1 / 2.54
LBL_T = r"Time since pitch step $t$ (s)"


def save(fig, name):
    OUTDIR.mkdir(parents=True, exist_ok=True)
    fig.savefig(OUTDIR / f"{name}.pdf", bbox_inches="tight", pad_inches=0.02)
    fig.savefig(OUTDIR / f"{name}.png", bbox_inches="tight", pad_inches=0.02)
    plt.close(fig)
    print("saved", OUTDIR / f"{name}.pdf")


def reference_step(ax, xlim, pc=0.3):
    ax.plot([xlim[0], 0, 0, xlim[1]], deg([0, 0, pc, pc]), "--", color=BLACK, lw=LW_REF, zorder=1)


def panel_letter(ax, letter):
    ax.set_title(f"({letter})", loc="left", fontsize=FONT_PT, pad=3)


def end_labels(ax, items, x, min_gap, dx=0.012):
    """Write each curve's name at its right-hand end instead of using a legend.
    items: list of (y_end, text, colour). Labels are pushed apart to at least min_gap."""
    items = sorted(items, key=lambda it: it[0])
    ys = [it[0] for it in items]
    for i in range(1, len(ys)):
        ys[i] = max(ys[i], ys[i - 1] + min_gap)
    for y, (_, text, col) in zip(ys, items):
        ax.text(1 + dx, y, text, color=col, transform=ax.get_yaxis_transform(), ha="left", va="center",
                fontsize=FONT_PT - 1, clip_on=False)


def y_end(t, y, x):
    return float(np.mean(y[(t > x - 1.0) & (t <= x)]))


# ============================ FIGURE 1: LQR without integral action (2 x 2) ============================
# (a) the first seconds: do the gains change the speed?      (b) the long run: the drift
# (c) the input during the step                              (d) travel rate, which the drift follows
runs = [("Sluggish", GREEN, r"$10R$"), ("Baseline", BLUE, "Baseline"),
        ("CheapVd", PURPLE, r"$0.1\,r_{V_d}$"), ("Aggressive", ORANGE, r"$10Q$")]
fig, axs = plt.subplots(2, 2, figsize=(TEXTWIDTH_CM * CM, 9.2 * CM), sharex="col",
                        gridspec_kw=dict(height_ratios=[1.7, 1], width_ratios=[1, 1.35], hspace=0.28, wspace=0.36))
(a, b), (c, d) = axs
xa, xb = (-0.5, 4), (-1, 25)
for ax, xl in [(a, xa), (b, xb)]:
    reference_step(ax, xl); ax.set_xlim(xl); ax.set_ylim(-1, 20)
tm = np.arange(0, xb[1], 0.01)
for ax in (a, b):
    ax.plot(tm, deg(pitch_model(tm)), ":", color=GREY, lw=LW_MODEL, zorder=2)
labels = []
for run, col, lab in runs:
    r = load(f"{run}_pitch"); t = t_step(r)
    a.plot(t, deg(r["p"]), color=col, lw=LW_MEAS)
    b.plot(t, deg(r["p"]), color=col, lw=LW_MEAS)
    if run != "CheapVd":
        c.plot(t, smooth(r["Vd"]), color=col, lw=LW_INPUT)
    d.plot(t, deg(r["trav_rate"]), color=col, lw=LW_INPUT)
    labels.append((y_end(t, deg(r["p"]), xb[1]), lab, col))
labels.append((deg(0.3) + 1.2, "reference, model", GREY))
end_labels(b, labels, xb[1], min_gap=1.9)
a.set_ylabel(r"Pitch $p$ (deg)"); c.set_ylabel(r"$V_d$ (V)"); d.set_ylabel(r"Travel rate (deg/s)")
c.set_xlabel(LBL_T); d.set_xlabel(LBL_T)
for ax, k in zip((a, b, c, d), "abcd"):
    panel_letter(ax, k)
for ax in (a, b):
    ax.tick_params(axis="x", length=0)
fig.align_ylabels([a, c])
save(fig, "p2_pitch_lqr")

# ============================ FIGURE 2: individual pitch weights (one panel) ============================
xlim = (-0.5, 10)
fig, ax = plt.subplots(figsize=(TEXTWIDTH_CM * CM, 5.0 * CM))
reference_step(ax, xlim)
tm = np.arange(0, xlim[1], 0.01)
ax.plot(tm, deg(pitch_model(tm)), ":", color=GREY, lw=LW_MODEL, zorder=2)
labels = [(deg(0.3) + 1.0, "reference, model", GREY)]
for run, col, lab in [("PitchDamp", GREEN, r"$10\,q_{\dot p}$"), ("Baseline", BLUE, "Baseline"),
                      ("PitchPrio", ORANGE, r"$10\,q_p$")]:
    r = load(f"{run}_pitch"); t = t_step(r)
    ax.plot(t, deg(r["p"]), color=col, lw=LW_MEAS)
    labels.append((y_end(t, deg(r["p"]), xlim[1]), lab, col))
end_labels(ax, labels, xlim[1], min_gap=1.9)
ax.set_xlim(xlim); ax.set_ylim(-1, 20); ax.set_ylabel(r"Pitch $p$ (deg)"); ax.set_xlabel(LBL_T)
save(fig, "p2_pitch_weights")

# ============================ FIGURE 3: elevation-rate pulse ============================
xlim = (-0.5, 5)
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(TEXTWIDTH_CM * CM, 8.0 * CM),
                               gridspec_kw=dict(height_ratios=[2.3, 1], hspace=0.10))
for ax in (ax1, ax2):
    ax.axvspan(0, 3, color="#f0f0f0", lw=0, zorder=0)          # the pulse
base = load("Baseline_elev"); tb = t_pulse(base); w = (tb >= xlim[0]) & (tb <= xlim[1])
ax1.plot(tb[w], deg(base["edc"][w]), "--", color=BLACK, lw=LW_REF, label=r"Reference $\dot e_c$", zorder=1)
ax1.plot(tb[w], deg(elev_model(tb[w] - tb[w][0], base["edc"][w])), ":", color=GREY, lw=LW_MODEL,
         label="Model (Baseline)", zorder=2)
for run, col, lab in [("Sluggish", GREEN, r"$10R$"), ("Baseline", BLUE, "Baseline"),
                      ("IBaseline", PURPLE, r"$q_I = 1$"), ("Aggressive", ORANGE, r"$10Q$")]:
    r = load(f"{run}_elev"); t = t_pulse(r)
    ax1.plot(t, deg(smooth(r["e_rate"])), color=col, lw=LW_MEAS, label=lab)
    ax2.plot(t, smooth(r["Vs"]), color=col, lw=LW_INPUT)
vs_sat = 2 * V_SAT - Vs0                          # V_s~ where both motors reach 5 V (V_d = 0)
ax2.axhline(vs_sat, color=BLACK, lw=0.6, ls=(0, (4, 2)))
ax2.text(xlim[1], vs_sat, "motor limit ", ha="right", va="bottom", fontsize=TICK_PT)
h, l = ax1.get_legend_handles_labels(); order = [3, 5, 2, 4, 1, 0]
ax1.legend([h[i] for i in order], [l[i] for i in order], loc="upper right", ncol=3)
ax1.set_xlim(xlim); ax1.set_ylim(-4.5, 9.5); ax1.tick_params(axis="x", length=0)
ax1.set_ylabel(r"Elevation rate $\dot e$ (deg/s)"); ax2.set_ylabel(r"$\tilde V_s$ (V)")
ax2.set_xlabel(r"Time since start of pulse $t$ (s)")
fig.align_ylabels([ax1, ax2])
save(fig, "p2_elev_rate")

# ============================ FIGURE 4: integral action (one panel) ============================
xlim = (-1, 25)
fig, ax = plt.subplots(figsize=(TEXTWIDTH_CM * CM, 5.4 * CM))
reference_step(ax, xlim)
labels = [(deg(0.3) + 1.4, "reference", GREY)]
for run, col, lab in [("Baseline", BLUE, "No integral"), ("ILow", PURPLE, r"$q_I = 0.1$"),
                      ("IBaseline", ORANGE, r"$q_I = 1$"), ("IHigh", GREEN, r"$q_I = 10$")]:
    r = load(f"{run}_pitch"); t = t_step(r)
    ax.plot(t, deg(r["p"]), color=col, lw=LW_MEAS)
    labels.append((y_end(t, deg(r["p"]), xlim[1]), lab, col))
end_labels(ax, labels, xlim[1], min_gap=1.5)
ax.set_xlim(xlim); ax.set_ylim(-1, 23); ax.set_ylabel(r"Pitch $p$ (deg)"); ax.set_xlabel(LBL_T)
save(fig, "p2_integral")

# ============================ FIGURE 5: with and without feedforward ============================
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(TEXTWIDTH_CM * CM, 7.6 * CM),
                               gridspec_kw=dict(height_ratios=[2.3, 1], hspace=0.10))
reference_step(ax1, xlim)
tm = np.arange(0, xlim[1], 0.01)
for run, col, lab, with_F in [("IBaseline", ORANGE, r"With $F$", True), ("IBaselineNoF", BLUE, r"$F = 0$", False)]:
    r = load(f"{run}_pitch"); t = t_step(r)
    ax1.plot(t, deg(r["p"]), color=col, lw=LW_MEAS, label=lab)
    ax1.plot(tm, deg(pitch_model_integral(tm, with_F)), ":", color=col, lw=LW_MODEL)
    ax2.plot(t, smooth(r["Vd"]), color=col, lw=LW_INPUT)
ax1.plot([], [], ":", color=GREY, lw=LW_MODEL, label="Model")
ax1.plot([], [], "--", color=BLACK, lw=LW_REF, label=r"Reference $p_c$")
ax1.legend(loc="lower right", ncol=2)
ax1.set_xlim(xlim); ax1.set_ylim(-1, 23); ax1.tick_params(axis="x", length=0)
ax1.set_ylabel(r"Pitch $p$ (deg)"); ax2.set_ylabel(r"$V_d$ (V)"); ax2.set_xlabel(LBL_T)
fig.align_ylabels([ax1, ax2])
save(fig, "p2_feedforward")
