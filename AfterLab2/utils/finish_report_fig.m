function finish_report_fig(ax, S, xlab, ylabs, xl, yls, fname, ratio)
% FINISH_REPORT_FIG  Labels, limits, legend + group template, then export.
%   ax     axes from new_report_fig (one or several panels)
%   xlab   x label (bottom panel only)
%   ylabs  y label, or cell array with one label per panel
%   xl     x limits ([] = automatic)
%   yls    y limits, or cell array with one entry per panel ([] = automatic)
%   fname  file name without extension
%   ratio  optional height/width (default S.ratio for one panel, S.ratio_multi for several)
    n = numel(ax);
    if ~iscell(ylabs), ylabs = {ylabs}; end
    if ~iscell(yls),   yls   = {yls};   end
    if nargin < 8 || isempty(ratio)
        if n == 1, ratio = S.ratio; else, ratio = S.ratio_multi; end
    end
    hfig = ancestor(ax(1), 'figure');
    set(hfig, 'Units', 'centimeters', 'Position', [3 3 S.width ratio*S.width])

    % --- labels, limits, legend ---
    for k = 1:n
        ylabel(ax(k), ylabs{k});
        if k <= numel(yls) && ~isempty(yls{k}), ylim(ax(k), yls{k}); end
        if S.grid, grid(ax(k), 'on'); else, grid(ax(k), 'off'); end
        set(ax(k), 'TickDir', S.tickdir, 'LineWidth', S.axis_lw)
        if ~isempty(findobj(ax(k), 'Type', 'line', 'HandleVisibility', 'on'))
            lg = legend(ax(k), 'show');
            lg.Location   = S.legend_loc;
            lg.NumColumns = S.legend_cols;
        end
    end
    if n > 1, linkaxes(ax, 'x'); end
    if ~isempty(xl), xlim(ax(end), xl); end
    xlabel(ax(end), xlab);

    % --- group template ---
    set(findall(hfig, '-property', 'FontSize'), 'FontSize', S.font)
    set(findall(hfig, '-property', 'Box'), 'Box', 'off')
    set(findall(hfig, '-property', 'Interpreter'), 'Interpreter', 'latex')
    set(findall(hfig, '-property', 'TickLabelInterpreter'), 'TickLabelInterpreter', 'latex')

    % --- shared x-axis: same ticks everywhere, numbers only on the bottom panel ---
    drawnow
    for k = 1:n-1
        ax(k).XTick      = ax(end).XTick;
        ax(k).XTickLabel = [];
    end

    % --- export ---
    pos = get(hfig, 'Position');
    set(hfig, 'PaperPositionMode', 'Auto', 'PaperUnits', 'centimeters', 'PaperSize', [pos(3), pos(4)])
    if ~exist(S.outdir, 'dir'), mkdir(S.outdir); end
    f = fullfile(S.outdir, fname);
    if any(strcmp(S.formats, 'pdf')), print(hfig, f, '-dpdf', '-vector', '-fillpage'); end
    if any(strcmp(S.formats, 'png')), print(hfig, f, '-dpng', '-r300'); end
    fprintf('Saved %s\n', f);
end
