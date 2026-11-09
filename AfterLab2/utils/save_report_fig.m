function save_report_fig(hfig, fname, hw_ratio, outdir)
% SAVE_REPORT_FIG  Apply the group's figure template and export PDF + PNG.
%   save_report_fig(hfig, 'p2_integral')            % default hw_ratio 0.65
%   save_report_fig(hfig, 'p2_integral', 0.75)      % taller (two panels)
%   save_report_fig(hfig, 'p2_integral', 0.75, outdir)
%
% Same settings as the group template, so every figure in the report looks
% the same. The PDF (vector) goes into LaTeX; the PNG is for quick viewing.

if nargin < 3 || isempty(hw_ratio), hw_ratio = 0.65; end
if nargin < 4 || isempty(outdir),   outdir   = fullfile('figures', 'report'); end
if ~exist(outdir, 'dir'), mkdir(outdir); end

picturewidth = 20;                                   % [cm] keep fixed for all figures
set(findall(hfig, '-property', 'FontSize'), 'FontSize', 17)
set(findall(hfig, '-property', 'Box'), 'Box', 'off')
set(findall(hfig, '-property', 'Interpreter'), 'Interpreter', 'latex')
set(findall(hfig, '-property', 'TickLabelInterpreter'), 'TickLabelInterpreter', 'latex')
set(hfig, 'Units', 'centimeters', 'Position', [3 3 picturewidth hw_ratio*picturewidth])
pos = get(hfig, 'Position');
set(hfig, 'PaperPositionMode', 'Auto', 'PaperUnits', 'centimeters', 'PaperSize', [pos(3), pos(4)])

print(hfig, fullfile(outdir, fname), '-dpdf', '-vector', '-fillpage')    % as AfterLab1/Task_2.m
print(hfig, fullfile(outdir, fname), '-dpng', '-r300')                  % preview only
fprintf('Saved %s.pdf / .png\n', fullfile(outdir, fname));
end
