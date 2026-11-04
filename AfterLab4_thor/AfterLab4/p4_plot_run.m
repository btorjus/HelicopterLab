function p4_plot_run(name)
% P4_PLOT_RUN  Raw IMU vs Kalman estimate vs encoder for one saved run,
%              plus sqrt(diag(P_hat)) and the new-data signal.
%   p4_plot_run('Qd_Baseline')
%
% Noisiest signal (raw IMU) is drawn first so it ends up in the back.
addpath('utils');
run = load_run_p4(name);
t   = run.tk;
if ~exist('figures', 'dir'), mkdir('figures'); end

lbl  = {'p [rad]','\dot{p} [rad/s]','e [rad]','\dot{e} [rad/s]','\lambda [rad]','\dot{\lambda} [rad/s]'};
yrow = [1 2 3 4 NaN 5];                 % row in y for each state (lambda not measured)
c_imu = [0.75 0.75 0.75];  c_enc = [0 0.45 0.74];  c_kf = [0.85 0.33 0.10];

figure('Name', ['States - ' name], 'Position', [80 80 1200 800]);
for i = 1:6
    subplot(3, 2, i); hold on; grid on;
    if ~isnan(yrow(i))
        plot(t, run.y(yrow(i), :), 'Color', c_imu, 'DisplayName', 'IMU (raw)');
    end
    plot(run.t, run.enc(i, :), 'Color', c_enc, 'LineWidth', 1.2, 'DisplayName', 'Encoder');
    plot(t, run.x_hat(i, :), 'Color', c_kf, 'LineWidth', 1.2, 'DisplayName', 'Kalman estimate');
    ylabel(['$' lbl{i} '$'], 'Interpreter', 'latex'); xlabel('t [s]');
    if i == 1, legend('Location', 'best'); end
end
sgtitle(strrep(name, '_', ' '));
saveas(gcf, fullfile('figures', ['p4_states_' name '.png']));

figure('Name', ['Covariance - ' name], 'Position', [100 100 1200 600]);
subplot(2, 1, 1);
semilogy(t, sqrt(abs(run.P_diag(1:6, :))).'); grid on;
legend({'p','pdot','e','edot','lambda','lambdadot'}, 'Location', 'best');
ylabel('sqrt(diag(P\_hat))'); title('Estimate standard deviation');
subplot(2, 1, 2);
stairs(t, run.new_data); ylim([-0.1 1.1]); grid on;
ylabel('new data'); xlabel('t [s]');
saveas(gcf, fullfile('figures', ['p4_cov_' name '.png']));

if run.n > 6
    figure('Name', ['Bias estimates - ' name]);
    plot(t, run.x_hat(7:end, :).'); grid on;
    xlabel('t [s]'); ylabel('bias'); title('Estimated IMU biases');
    saveas(gcf, fullfile('figures', ['p4_bias_' name '.png']));
end

% Estimation error vs encoder (RMS after start-up)
k   = t > 5;
err = run.x_hat([1 2 3 4 6], k) - interp1(run.t, run.enc([1 2 3 4 6], :).', t(k)).';
fprintf('%s  RMS(x_hat - encoder) [p pdot e edot ldot] = [%s]\n', ...
        name, num2str(sqrt(mean(err.^2, 2)).', '%.4f  '));
end
