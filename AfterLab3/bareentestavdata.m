d = load_p3('T2_euler_enc');

% 1) Right number of columns and full length
fprintf('Duration: %.1f s\n', d.t(end));        % should match how long you ran
fprintf('enc %d, gyro %d, acc %d, new %d, y %d columns\n', ...
    size(d.enc,2), size(d.gyro,2), size(d.acc,2), size(d.new,2), size(d.y,2));
% expected: 6, 3, 3, 1, 5

% 2) IMU actually delivered data
fprintf('New IMU samples: %d\n', sum(d.new));    % should be well above 0
fprintf('|acc| mean: %.2f m/s^2\n', mean(vecnorm(d.acc,2,2)));  % ~9.81 if mostly still

% 3) Visual check: transformed IMU vs encoders
figure
subplot(2,1,1); hold on; grid on
plot(d.t, d.enc(:,3), d.t, d.y(:,1));
plot(d.t, d.enc(:,5), d.t, d.y(:,3));
legend('p enc', 'p IMU', 'e enc', 'e IMU'); ylabel('Angle [rad]')

subplot(2,1,2); hold on; grid on
plot(d.t, d.enc(:,4), d.t, d.y(:,2));
plot(d.t, d.enc(:,6), d.t, d.y(:,4));
plot(d.t, d.enc(:,2), d.t, d.y(:,5));
legend('p\_dot enc', 'p\_dot IMU', 'e\_dot enc', 'e\_dot IMU', ...
       '\lambda\_dot enc', '\lambda\_dot IMU');
xlabel('Time [s]'); ylabel('Rate [rad/s]')