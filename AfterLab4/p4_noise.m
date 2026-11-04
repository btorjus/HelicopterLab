%% p4_noise.m - Part IV Task 1: measurement noise covariance Rd
% Record two runs with heli_p4_kalman: heli resting on the table, and heli
% hovering at the linearization point. Save them with save_run_p4 first.
addpath('utils');

ground = load_run_p4('T4_noise_ground');   % <-- your run names
hover  = load_run_p4('T4_noise_hover');

% Use only samples where the IMU actually delivered new data;
% repeated (held) samples would underestimate the covariance.
% Hover: use only the stationary part (skip takeoff and settling).
t_hover = [10 40];                         % [s] <-- adjust after looking at the plot
in_win  = hover.t >= t_hover(1) & hover.t <= t_hover(2);

Y_g = ground.y(ground.new > 0.5, :);       % N x 5 (one column per measurement)
Y_h = hover.y(hover.new > 0.5 & in_win, :);

% Remove slow drift (real motion, not noise) with a linear detrend per column.
% The controller holds e_dot, not e, so e can drift slowly in hover.
var_before = var(Y_h);
Y_g = detrend(Y_g);
Y_h = detrend(Y_h);
fprintf('Hover variance removed by detrend [p pdot e edot ldot]: %s %%\n', ...
        mat2str(round(100*(1 - var(Y_h)./var_before)), 3));

% Quick check that the hover window really is stationary
figure; plot(hover.t, hover.enc(:,5)); hold on; grid on
xline(t_hover(1), '--'); xline(t_hover(2), '--');
xlabel('t [s]'); ylabel('e (encoder) [rad]'); title('Hover run: window used for R_d');

R_ground = cov(Y_g);
R_hover  = cov(Y_h);

names = {'p','p_dot','e','e_dot','lambda_dot'};
fprintf('%-11s %12s %12s %8s\n', 'meas', 'var ground', 'var hover', 'ratio');
for i = 1:5
    fprintf('%-11s %12.3e %12.3e %8.1f\n', names{i}, R_ground(i,i), R_hover(i,i), ...
            R_hover(i,i)/R_ground(i,i));
end

Rd = R_hover;                  % flying covariance is used in the filter
save('Rd_flying.mat', 'Rd');
fprintf('\nSaved Rd_flying.mat (from hover run)\n');
