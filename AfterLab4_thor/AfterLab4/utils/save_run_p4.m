function save_run_p4(name)
% SAVE_RUN_P4  Copy the fixed-name Part IV logs to named copies in data/p4/.
%   save_run_p4('Noise_ground'), save_run_p4('Qd_Zero'), ...
%   p4Run.mat contains everything (encoders, IMU, x_hat, P_diag, ...).
%   Heli3D.mat (encoder-only log) is copied too as a backup if it exists.
    outdir = fullfile('data', 'p4');
    if ~exist(outdir, 'dir'), mkdir(outdir); end
    copyfile('p4Run.mat', fullfile(outdir, ['p4Run_' name '.mat']), 'f');
    if exist('Heli3D.mat', 'file')
        copyfile('Heli3D.mat', fullfile(outdir, ['Heli3D_' name '.mat']), 'f');
    end
    fprintf('Saved run: %s\n', name);
end
