function save_run_p2(name)
% Copies the fixed-name Part II log files to named copies in data/p2/
    outdir = fullfile('data','p2');
    if ~exist(outdir,'dir'), mkdir(outdir); end
    copyfile('HeliRun.mat', fullfile(outdir, ['HeliRun_' name '.mat']), 'f');
    copyfile('p2Run.mat',   fullfile(outdir, ['p2Run_'   name '.mat']), 'f');
    fprintf('Saved run: %s\n', name);
end