%% p4_noise_estimate.m — Part IV Task 1: measurement noise Rd
% Procedure at the lab:
%   1. Run heli_p4_kalman with the helicopter LYING STILL on the ground
%      (~30 s, no joystick), stop, then:  save_run_p4('Noise_ground')
%   2. Fly and hold the helicopter STATIONARY at the linearization point
%      (p = 0, e = 0) with the controller (~30 s), then: save_run_p4('Noise_hover')
%   3. Run this script -> writes data/p4/Rd.mat, which p4_kalman.m loads.
%
% Two ways of forming the noise sequence (choose with use_encoder_ref):
%   false : v = y - mean(y)          (literal "covariance of the time series")
%   true  : v = y - y_encoder        (removes slow motion that is not noise
%                                     while flying; encoders are almost noise-free)
% cov() removes the mean in both cases, so constant IMU biases do not matter.

clear; clc; close all;
addpath('utils');

runs            = {'Noise_ground', 'Noise_hover'};
t_skip          = 5;        % [s] skip start-up transient
use_encoder_ref = true;
max_lag         = 50;       % autocorrelation lags (in IMU samples)
meas_names = {'p','pdot','e','edot','lambdadot'};
meas_units = {'rad','rad/s','rad','rad/s','rad/s'};

if ~exist('figures', 'dir'), mkdir('figures'); end
R = cell(1, numel(runs));
V = cell(1, numel(runs));

for r = 1:numel(runs)
    run = load_run_p4(runs{r});

    % Only use samples where the IMU actually delivered a new value;
    % the held samples in between would bias the autocorrelation.
    idx = find(run.new_data > 0.5 & run.tk > t_skip);
    imu_rate = numel(find(run.new_data > 0.5)) / (run.tk(end) - run.tk(1));

    Y = run.y(:, idx).';                                    % N x 5 (one column per measurement)
    E = run.enc([1 2 3 4 6], idx).';                        % encoder counterpart
    if use_encoder_ref, Vk = Y - E; else, Vk = Y; end

    R{r} = cov(Vk);                                         % 5 x 5
    V{r} = Vk - mean(Vk, 1);

    fprintf('\n=== %s:  N = %d samples, IMU rate ~ %.1f Hz ===\n', runs{r}, size(Vk,1), imu_rate);
    fprintf('%-10s %12s %12s\n', 'meas', 'variance', 'std');
    for j = 1:5
        fprintf('%-10s %12.3e %12.3e  [%s]\n', meas_names{j}, R{r}(j,j), sqrt(R{r}(j,j)), meas_units{j});
    end
    disp('Full covariance:'); disp(R{r});
    disp('Correlation coefficients:'); disp(corrcoef(Vk));
end

%% ---------- Compare ground vs flying ----------
fprintf('\nVariance ratio  flying / ground:\n');
for j = 1:5
    fprintf('  %-10s %8.1f\n', meas_names{j}, R{2}(j,j) / R{1}(j,j));
end
% Expect a large increase while flying: motor/propeller vibrations hit the
% accelerometer directly (and the gyro to a lesser degree), plus small
% unmodelled motion. The ground run is (almost) pure sensor noise.

%% ---------- Autocorrelation (white-noise check) ----------
figure('Name', 'Noise autocorrelation', 'Position', [100 100 1100 600]);
for j = 1:5
    subplot(2, 3, j); hold on; grid on;
    for r = 1:numel(runs)
        v  = V{r}(:, j);
        N  = numel(v);
        ac = zeros(max_lag+1, 1);
        for k = 0:max_lag
            ac(k+1) = sum(v(1:N-k) .* v(1+k:N)) / sum(v.^2);
        end
        stem(0:max_lag, ac, 'filled', 'MarkerSize', 3, 'DisplayName', strrep(runs{r}, '_', ' '));
    end
    yline( 1.96/sqrt(N), 'k--', 'HandleVisibility', 'off');
    yline(-1.96/sqrt(N), 'k--', 'HandleVisibility', 'off');
    title(meas_names{j}); xlabel('lag [IMU samples]'); ylabel('\rho');
    if j == 1, legend('Location', 'northeast'); end
end
saveas(gcf, fullfile('figures', 'p4_noise_autocorr.png'));

%% ---------- Time series + histogram ----------
figure('Name', 'Noise time series', 'Position', [100 100 1100 800]);
for j = 1:5
    for r = 1:numel(runs)
        subplot(5, 3, 3*(j-1) + r);
        plot(V{r}(:, j)); grid on;
        title(sprintf('%s - %s', strrep(runs{r}, '_', ' '), meas_names{j}));
    end
    subplot(5, 3, 3*j); hold on; grid on;
    for r = 1:numel(runs)
        histogram(V{r}(:, j), 60, 'Normalization', 'pdf', 'DisplayStyle', 'stairs');
    end
    title([meas_names{j} ' histogram']);
end
saveas(gcf, fullfile('figures', 'p4_noise_timeseries.png'));

%% ---------- Save Rd (flying covariance) ----------
Rd        = R{2};
Rd_ground = R{1};
Rd_hover  = R{2};
save(fullfile('data', 'p4', 'Rd.mat'), 'Rd', 'Rd_ground', 'Rd_hover', 'imu_rate', 'use_encoder_ref');
fprintf('\nSaved data/p4/Rd.mat  (Rd = flying covariance)\n');
