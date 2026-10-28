function save_p3(tag)
% Usage right after a run:  save_p3('T2_pitch_acc_vs_enc')
copyfile('p3Run.mat', ['p3_' tag '.mat'], 'f');
evalin('base', sprintf(['save(''p3_%s_params.mat'', ''-regexp'', ' ...
    '''^(L|L_min|obs_poles|C_obs|K|F|Q|R)$'')'], tag));
fprintf('Saved run %s\n', tag);
end