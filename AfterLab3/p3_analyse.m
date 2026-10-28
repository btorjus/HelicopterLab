%% p3_analyse.m - sammenligner observatortester (Part III)
% Fyll inn taggene som skal sammenlignes. Alle kjoringer bruker samme
% referanseprofil, sa de kan plottes oppa hverandre.
clear; clc;
addpath('utils');

tags   = {'T3_test2_cl', 'T3_test3_cl', 'T3_test1_cl', 'T3_test7_cl'};
labels = {'Treg', 'Balansert', 'Rask', 'Veldig rask'};

t_eval  = 5;          % evaluer feil etter takeoff [s] (unngar startkonvergens)
t_hover = [5 8];      % stasjonaer hover i referanseprofilen [s]
t_sine  = [30 42];    % pitch-sinus [s]

% x_hat = [p p_dot e e_dot lambda_dot]
% enc   = [lambda lambda_dot p p_dot e e_dot]
enc_idx = [3 4 5 6 2];

farger = ["#3B9AB2" "#F21A00" "#E1AF00" "#78B7C5" "#5B1A18"];

%% Last inn og regn ut nokkeltall
n = numel(tags);
D = cell(1, n);
fprintf('RMS estimeringsfeil etter t = %g s, og stoy pa Vd i hover\n\n', t_eval);
fprintf('%-12s %8s %8s %8s %8s %8s %10s\n', ...
        'Test', 'p', 'p_dot', 'e', 'e_dot', 'l_dot', 'std(Vd)');
for k = 1:n
    d = load_p3(tags{k});
    assert(~isempty(d.xhat), '%s: x_hat er ikke logget', tags{k});
    D{k} = d;

    m    = d.t >= t_eval;
    err  = d.xhat(m,:) - d.enc(m, enc_idx);
    rmse = sqrt(mean(err.^2, 1, 'omitnan'));

    h = d.t >= t_hover(1) & d.t <= t_hover(2);
    fprintf('%-12s %8.3f %8.3f %8.3f %8.3f %8.3f %10.3f\n', ...
            labels{k}, rmse, std(d.u(h,2)));
end

%% Figur 1: estimeringsfeil over tid
f1 = figure('Name', 'Estimeringsfeil');
tiledlayout(2, 1, 'TileSpacing', 'compact');

nexttile; hold on; grid on
for k = 1:n
    d = D{k};
    plot(d.t, d.xhat(:,1) - d.enc(:,3), 'Color', farger(k), 'DisplayName', labels{k});
end
ylabel('$\hat p - p$ [rad]', 'Interpreter', 'latex');
legend('Location', 'best');

nexttile; hold on; grid on
for k = 1:n
    d = D{k};
    plot(d.t, d.xhat(:,4) - d.enc(:,6), 'Color', farger(k), 'DisplayName', labels{k});
end
ylabel('$\hat{\dot e} - \dot e$ [rad/s]', 'Interpreter', 'latex');
xlabel('Tid [s]', 'Interpreter', 'latex');

%% Figur 2: pitch under sinus - etterslep
f2 = figure('Name', 'Pitch under sinus');
tiledlayout(n, 1, 'TileSpacing', 'compact');
for k = 1:n
    d = D{k};
    s = d.t >= t_sine(1) & d.t <= t_sine(2);
    nexttile; hold on; grid on
    plot(d.t(s), d.ref(s,1),  'k--', 'DisplayName', '$p_c$');
    plot(d.t(s), d.enc(s,3),  'Color', farger(1), 'DisplayName', '$p$ (enkoder)');
    plot(d.t(s), d.xhat(s,1), 'Color', farger(2), 'DisplayName', '$\hat p$');
    title(labels{k}, 'Interpreter', 'latex');
    ylabel('[rad]', 'Interpreter', 'latex');
    if k == 1, legend('Interpreter', 'latex', 'Location', 'best'); end
end
xlabel('Tid [s]', 'Interpreter', 'latex');

%% Figur 3: Vd i hover - stoy til motorene
f3 = figure('Name', 'Vd i hover');
hold on; grid on
for k = 1:n
    d = D{k};
    h = d.t >= t_hover(1) & d.t <= t_hover(2);
    plot(d.t(h), d.u(h,2), 'Color', farger(k), 'DisplayName', labels{k});
end
xlabel('Tid [s]', 'Interpreter', 'latex');
ylabel('$V_d$ [V]', 'Interpreter', 'latex');
legend('Location', 'best');

%% Eksport til rapporten (fjern kommentar ved behov)
% exportgraphics(f1, 'p3_estimeringsfeil.pdf', 'ContentType', 'vector');
% exportgraphics(f2, 'p3_pitch_sinus.pdf',     'ContentType', 'vector');
% exportgraphics(f3, 'p3_vd_hover.pdf',        'ContentType', 'vector');
