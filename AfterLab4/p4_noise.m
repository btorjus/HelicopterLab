%% p4_noise.m - Part IV Task 1: measurement noise covariance Rd
% Record two runs with heli_p4_kalman: heli resting on the table, and heli
% hovering at the linearization point. Save them with save_run_p4 first.
addpath('utils');

ground = load_run_p4('T4_noise_ground');   % <-- your run names
hover  = load_run_p4('T4_noise_hover');

% Use only samples where the IMU actually delivered new data;
% repeated (held) samples would underestimate the covariance.
Y_g = ground.y(ground.new > 0.5, :);       % N x 5 (one column per measurement)
Y_h = hover.y(hover.new > 0.5, :);

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
