function d = load_run(config)
    pitch = load(['pitchdataRun_' config '.mat']);
    heli  = load(['HeliRun_'      config '.mat']);
    vs    = load(['Vs_'           config '.mat']);

    pitch_arr = pitch.(char(fieldnames(pitch)));
    heli_arr  = heli.(char(fieldnames(heli)));
    vs_arr    = vs.(char(fieldnames(vs)));

    d.t       = pitch_arr(1,:);
    d.p_c     = pitch_arr(2,:);
    d.error   = pitch_arr(3,:);
    d.Kpp     = pitch_arr(4,:);
    d.Kpd     = pitch_arr(5,:);
    d.Vd      = pitch_arr(6,:);

    d.travel      = heli_arr(2,:);
    d.travel_rate = heli_arr(3,:);
    d.pitch       = heli_arr(4,:);
    d.pitch_rate  = heli_arr(5,:);
    d.elevation   = heli_arr(6,:);
    d.elev_rate   = heli_arr(7,:);

    d.Vs = vs_arr(2,:);

    if length(heli_arr(1,:)) ~= length(d.t) || length(vs_arr(1,:)) ~= length(d.t)
        warning('Time vector length mismatch for run %s.', config);
    end
end