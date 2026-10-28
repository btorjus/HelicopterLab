function save_run_p4(tag)
% Usage right after a run:  save_run_p4('T4_test1_par')
% Copies p4Run.mat to data/p4/p4_<tag>.mat and saves the filter settings.
outdir = fullfile('data','p4');
if ~exist(outdir,'dir'), mkdir(outdir); end
copyfile('p4Run.mat', fullfile(outdir, ['p4_' tag '.mat']), 'f');
evalin('base', sprintf(['save(''%s'', ''-regexp'', ' ...
    '''^(Qd|Rd|Rd_use|P0|x0|TEST|use_est|K|F|Ad|Bd|Cd)$'')'], ...
    fullfile(outdir, ['p4_' tag '_params.mat'])));
fprintf('Saved run %s\n', tag);
end
