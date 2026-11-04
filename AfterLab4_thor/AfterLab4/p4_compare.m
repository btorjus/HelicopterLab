%% p4_compare.m — Part IV Task 3: overlay several Qd experiments for one state
% Example: compare Qd = 0, Baseline and Inf on pitch.
clear; clc; close all;
addpath('utils');

names = {'Qd_Zero', 'Qd_Baseline', 'Qd_Inf'};   % saved with save_run_p4(...)
state = 1;                 % 1 p | 2 pdot | 3 e | 4 edot | 6 lambdadot
t_win = [0 30];            % [s]

lbl  = {'p [rad]','pdot [rad/s]','e [rad]','edot [rad/s]','lambda [rad]','lambdadot [rad/s]'};
yrow = [1 2 3 4 NaN 5];

figure('Position', [100 100 1100 500]); hold on; grid on;
ref = load_run_p4(names{1});
if ~isnan(yrow(state))
    plot(ref.tk, ref.y(yrow(state), :), 'Color', [0.8 0.8 0.8], 'DisplayName', ['IMU raw (' strrep(names{1},'_',' ') ')']);
end
for i = 1:numel(names)
    run = load_run_p4(names{i});
    plot(run.t,  run.enc(state, :), '--', 'DisplayName', ['Encoder ' strrep(names{i},'_',' ')]);
    plot(run.tk, run.x_hat(state, :), 'LineWidth', 1.3, 'DisplayName', ['KF ' strrep(names{i},'_',' ')]);
end
xlim(t_win); xlabel('t [s]'); ylabel(lbl{state}); legend('Location', 'best');
title(['Kalman filter, varying Q_d: ' lbl{state}]);
if ~exist('figures', 'dir'), mkdir('figures'); end
saveas(gcf, fullfile('figures', sprintf('p4_compare_state%d.png', state)));
