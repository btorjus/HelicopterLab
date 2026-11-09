function ax = new_report_fig(n, heights)
% NEW_REPORT_FIG  New figure with n stacked panels sharing the x-axis.
%   ax = new_report_fig()           one panel
%   ax = new_report_fig(2)          two panels, equal height
%   ax = new_report_fig(2, [2 1])   two panels, top panel twice as tall
    if nargin < 1, n = 1; end
    if nargin < 2, heights = ones(1, n); end
    figure('Color', 'w');
    tl = tiledlayout(sum(heights), 1, 'TileSpacing', 'compact', 'Padding', 'compact');
    ax = gobjects(1, n);
    for k = 1:n
        ax(k) = nexttile(tl, [heights(k) 1]);
        hold(ax(k), 'on');
    end
end
