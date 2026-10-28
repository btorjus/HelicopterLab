function run = load_run_p2(name)
% Loads a named Part II run into one struct
    d = fullfile('data','p2');
    H = load(fullfile(d, ['HeliRun_' name '.mat'])); fn = fieldnames(H); H = H.(fn{1});
    P = load(fullfile(d, ['p2Run_'   name '.mat'])); fn = fieldnames(P); P = P.(fn{1});

    run.t      = H(1,:);
    run.travel = H(2,:);  run.travel_rate = H(3,:);
    run.p      = H(4,:);  run.p_rate      = H(5,:);
    run.e      = H(6,:);  run.e_rate      = H(7,:);

    run.pc     = P(2,:);  run.edot_c = P(3,:);
    run.Vs_til = P(4,:);  run.Vd     = P(5,:);
end