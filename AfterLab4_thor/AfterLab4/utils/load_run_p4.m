function run = load_run_p4(name)
% LOAD_RUN_P4  Load a named Part IV run (data/p4/p4Run_<name>.mat) into a struct.
%
% Layout = logging Mux1 in heli_p4_kalman_kf.slx ("To File" -> p4Run.mat, Array):
%   row 1   t                                        (added automatically)
%   in 1    encoders (6)   [travel; travel_rate; p; p_rate; e; e_rate]
%   in 2    gyro raw (3)
%   in 3    acc raw (3)
%   in 4    new data (1)   (after the manual switch)
%   in 5    y (5)          [p; pdot; e; edot; lambdadot] from IMU
%   in 6    x_hat (n)      n = 6 (+ bias states)
%   in 7    reference (2)  [p_c; edot_c]
%   in 8    motor (2)      [Vs; Vd]   (Vs incl. Vs0)
%   in 9    P_diag (n)
    d = fullfile('data', 'p4');
    P = load(fullfile(d, ['p4Run_' name '.mat'])); fn = fieldnames(P); P = P.(fn{1});

    n = (size(P, 1) - 23) / 2;
    assert(n == round(n) && n >= 6, ...
           'p4Run has %d rows - check the logging Mux (expected 23 + 2n)', size(P, 1));

    i = 1;
    run.name = name;
    run.t    = P(i, :);              i = i + 1;
    E        = P(i:i+5, :);          i = i + 6;
    run.gyro_raw = P(i:i+2, :);      i = i + 3;
    run.acc_raw  = P(i:i+2, :);      i = i + 3;
    run.new_data = P(i, :);          i = i + 1;
    run.y        = P(i:i+4, :);      i = i + 5;
    run.x_hat    = P(i:i+n-1, :);    i = i + n;
    run.r        = P(i:i+1, :);      i = i + 2;
    run.Vs       = P(i, :);          run.Vd = P(i+1, :);   i = i + 2;
    run.P_diag   = P(i:i+n-1, :);

    run.travel = E(1,:);  run.travel_rate = E(2,:);
    run.p      = E(3,:);  run.p_rate      = E(4,:);
    run.e      = E(5,:);  run.e_rate      = E(6,:);
    % Elevation encoder offset (Part I Task 2.1.2 never applied in Simulink)
    run.e_offset = heli_e_offset();
    run.e_raw    = run.e;
    run.e        = run.e - run.e_offset;
    % encoder in estimator-state order [p pdot e edot lambda lambdadot]
    run.enc    = [run.p; run.p_rate; run.e; run.e_rate; run.travel; run.travel_rate];
    run.tk     = run.t;      % same time base (one To File block)
    run.n      = n;
end
