# Del IV – Kalmanfilter

## Filer
| Fil | Hva |
|---|---|
| `finish_p4_model.m` | Kobler ferdig toppnivået i `heli_p4_kalman.slx` og lagrer som `heli_p4_kalman_kf.slx`. |
| `p4_kalman.m` | **Hovedskript.** Kjøres før QuaRC Build. Regulator (LQR/LQRI fra del II), 6-tilstandsmodell, `c2d` (Ts = 0.002), `Ad Bd Cd`, `Rd` (lastes fra `data/p4/Rd.mat`), `Qd`, `x0`, `P0`, observerbarhet og stasjonær Kalman-forsterkning/ekvivalente poler (for å sammenligne med Luenberger-polene fra del III). |
| `kf_predict.m` | Kode til MATLAB Function-blokken for prediksjon (2.21d–e). |
| `kf_correct.m` | Kode til MATLAB Function-blokken for korreksjon (2.21a–c), bare når `new_data = 1`, ellers `x̂ = x̄`, `P̂ = P̄`. |
| `p4_noise_estimate.m` | Oppgave 1: kovarians bakke vs. sveve, autokorrelasjon, lagrer `Rd`. |
| `p4_plot_run.m` | Plott rå IMU / Kalman / encoder + `sqrt(diag(P̂))` og new-data for én kjøring. |
| `p4_compare.m` | Overlegg flere Qd-eksperimenter for én tilstand. |
| `utils/p4_qd.m` | Qd-testplan: `Baseline` (Van Loan), `Zero`, `Inf`, `Low`, `High`, `PitchHigh`, `ElevHigh`. |
| `utils/van_loan.m` | Bonus 1: eksakt diskretisering av prosesstøy. |
| `utils/save_run_p4.m`, `load_run_p4.m` | Lagre/laste navngitte kjøringer i `data/p4/`. |

## Simulink – `heli_p4_kalman.slx`
Kalman-subsystemet (`kf_correct`, `kf_predict`, Unit Delay med `x0`/`P0`, utgang `P_diag`) og bryteren på new-data er ferdig. Resten på toppnivå kobles av skriptet:

```matlab
p4_kalman            % lager Ad, Bd, Cd, Qd, Rd, x0, P0, K, F, ref_profile ...
finish_p4_model      % heli_p4_kalman.slx -> heli_p4_kalman_kf.slx (originalen røres ikke)
```

`finish_p4_model` gjør dette:
1. `Mux3 = [V~s; V~d]` går til Kalman Filter inn 2 (u).
2. `x_hat` går til Demux, som nå har 6 utganger, og videre til LQR controller (p, ṗ, e, ė).
3. `x_hat` går til logge-Mux1 inn 6, og `P_diag` til ny inngang 9.
4. Logget new-data tas etter bryteren.
5. `x_hat` blir inngang 3 i de fem `*_imu v *`-scopene.
6. To File endres fra `p3Run.mat` til `p4Run.mat`.
7. Manuelle brytere velger mellom referanseprofil og joystick for p_c og ė_c.

`patch_p4_model.m` (hvis den finnes) gjaldt en eldre versjon av modellen og skal ikke brukes.

### Logging (`p4Run.mat`, rekkefølgen i Mux1, Array-format)
| Inngang | Signal | Rader |
|---|---|---|
| (tid) | t | 1 |
| 1 | encoder [λ, λ̇, p, ṗ, e, ė] | 6 |
| 2 | gyro rå | 3 |
| 3 | akselerometer rå | 3 |
| 4 | new data (etter bryter) | 1 |
| 5 | y = [p ṗ e ė λ̇] | 5 |
| 6 | x̂ | n |
| 7 | referanse [p_c, ė_c] | 2 |
| 8 | [Vs, Vd] til motor | 2 |
| 9 | diag(P̂) | n |

`load_run_p4` leser nettopp dette (23 + 2n rader).

## Gangen på lab
1. `p4_kalman` (med placeholder-Rd) → `finish_p4_model` (bare første gang) → Build `heli_p4_kalman_kf` → la heli ligge stille ~30 s → `save_run_p4('Noise_ground')`
2. Fly og hold i ro ved p = 0, e = 0 ~30 s → `save_run_p4('Noise_hover')`
3. `p4_noise_estimate` → lager `data/p4/Rd.mat`
4. `p4_kalman` på nytt (laster ekte Rd) → Build. Kjør testplanen ved å endre `Qd_cfg`, lagre hver med f.eks. `save_run_p4('Qd_Zero')`
5. Med/uten integralvirkning: `ctrl_type = 'LQR'` eller `'LQRI'` (husk at regulatorblokken må matche K: 2x3 vs 2x5).
6. Bonus 2 (bias): `use_bias = true`. Standard `bias_set = {'p','pdot','edot'}` er observerbart (rang 8/9, kun λ uobserverbar). Bias på `e` eller `lambdadot` er **ikke** observerbart med disse målingene.

## Ting å diskutere i rapporten
- **λ er uobserverbar** (ingen måling av λ og ingen andre tilstander avhenger av den) → `P̂(5,5)` vokser uten grense. Ufarlig, regulatoren bruker ikke λ.
- **Qd = 0**: forsterkningen L → 0, filteret stoler bare på modellen → estimatene driver (modellfeil, bias).
- **Qd = ∞**: L → målingene, x̂ ≈ y → ingen filtrering, støyen går rett til regulatoren.
- **Frakoblet new-data**: ren prediksjon (open-loop), `P̂` vokser monotont (Ad P Adᵀ + Qd); ved gjenkobling kollapser P̂ og x̂ hopper tilbake mot målingene.
- **Luenberger vs. Kalman**: samme struktur (prediksjon + forsterkning × innovasjon). Luenberger: fast L fra polplassering, korrigerer hvert steg (også med gamle data). Kalman: tidsvarierende L fra Qd/Rd, optimal (minimal feilvarians) under Gaussiske antakelser, håndterer manglende målinger naturlig. `p4_kalman.m` skriver ut de ekvivalente kontinuerlige polene til stasjonær Kalman for direkte sammenligning.
