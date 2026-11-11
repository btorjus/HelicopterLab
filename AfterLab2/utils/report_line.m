function h = report_line(ax, t, y, color, kind, name, S)
% REPORT_LINE  Plot one line in the report style.
%   report_line(ax, t, y, color, kind, name, S)
%
%   kind   'meas'   measured signal                    solid,  S.lw
%          'meas2'  measured, second style             solid,  S.lw   (dashed is unreadable on noisy data)
%          'model'  model prediction                   dotted, S.lw_model
%          'ref'    reference                          dashed, S.lw_ref
%          'input'  input voltage                      solid,  S.lw_input
%   name   legend text, '' = not shown in the legend
    switch kind
        case 'meas',  ls = '-';  lw = S.lw;
        case 'meas2', ls = '-';  lw = S.lw;
        case 'model', ls = ':';  lw = S.lw_model;
        case 'ref',   ls = '--'; lw = S.lw_ref;
        case 'input', ls = '-';  lw = S.lw_input;
        otherwise,    error('report_line: unknown kind "%s"', kind);
    end
    h = plot(ax, t, y, ls, 'Color', color, 'LineWidth', lw);
    if isempty(name)
        h.HandleVisibility = 'off';
    else
        h.DisplayName = name;
    end
end
