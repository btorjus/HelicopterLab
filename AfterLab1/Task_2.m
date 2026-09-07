%% Task 2
mc = 1.92;
lc = 0.46;
mp = 0.72;
ln = 0.66;
g = 9.81;
Vs0 = 7.3;
lp = 0.175;

Kf = (-(mc*lc - 2*mp*ln)*g) / (ln*Vs0);

K1 = Kf/(2*mp*lp);
%% Rename file
%copyfile('Heli3D.mat', 'HeliRun_MSStep04.mat', 'f');
%copyfile('pitchdata.mat', 'pitchdataRun_MSStep04.mat', 'f');
%copyfile('Vs.mat', 'Vs_MSStep04.mat', 'f');


%% Task 2 - Pitch controller comparison across pole configurations
clear; clc; close all

configs = {'UDStep04','CDStep04','ODStep04','MSStep04'};
labels  = {'Underdamped','Critically damped','Overdamped','Marginally stable'};

% Wes Anderson - Zissou1 inspired palette
colors = {'#3B9AB2', ...  % deep teal
          '#F21A00', ...  % deep red
          '#E1AF00', ...  % mustard/ochre
          '#78B7C5'};     % light blue
ref_color = '#5B1A18';    % dark maroon, for the dashed reference line

%% Load all runs and align step onset to t = 0
data = cell(1,length(configs));

for i = 1:length(configs)
    d = load_run(configs{i});

    threshold = 0.01 * max(abs(d.p_c - d.p_c(1)));
    if threshold == 0
        threshold = 1e-6;
    end
    onset_idx = find(abs(d.p_c - d.p_c(1)) > threshold, 1, 'first');

    if isempty(onset_idx)
        warning('No step detected in run %s — check p_c signal.', configs{i});
        onset_idx = 1;
    end

    t_onset = d.t(onset_idx);
    d.t = d.t - t_onset;

    data{i} = d;
end

%% Figure 1: Pitch response comparison
hfig = figure; hold on

for i = 1:length(configs)
    d = data{i};
    plot(d.t, rad2deg(d.pitch), 'Color', colors{i}, 'LineWidth', 1.8, ...
        'DisplayName', labels{i})
end

d_ref = data{1};
plot(d_ref.t, rad2deg(d_ref.p_c), '--', 'Color', ref_color, 'LineWidth', 1.2, ...
    'DisplayName', 'Reference $p_c$')

xlabel('time $t$ (s)')
ylabel('pitch $p$ (deg)')
legend('show','Location','best')
xlim([-0.5, 2])

fname = 'pitch_comparison_step04';
picturewidth = 20;
hw_ratio = 0.65;
set(findall(hfig,'-property','FontSize'),'FontSize',17)
set(findall(hfig,'-property','Box'),'Box','off')
set(findall(hfig,'-property','Interpreter'),'Interpreter','latex')
set(findall(hfig,'-property','TickLabelInterpreter'),'TickLabelInterpreter','latex')
set(hfig,'Units','centimeters','Position',[3 3 picturewidth hw_ratio*picturewidth])
pos = get(hfig,'Position');
set(hfig,'PaperPositionMode','Auto','PaperUnits','centimeters','PaperSize',[pos(3), pos(4)])
print(hfig,fname,'-dpdf','-vector','-fillpage')

%% Figure 2: Control effort (Vd) comparison
hfig2 = figure; hold on

for i = 1:length(configs)
    d = data{i};
    plot(d.t, d.Vd, 'Color', colors{i}, 'LineWidth', 1.8, 'DisplayName', labels{i})
end

xlabel('time $t$ (s)')
ylabel('$V_d$ (V)')
legend('show','Location','best')
xlim([-0.5, 2])

fname2 = 'Vd_comparison_step04';
set(findall(hfig2,'-property','FontSize'),'FontSize',17)
set(findall(hfig2,'-property','Box'),'Box','off')
set(findall(hfig2,'-property','Interpreter'),'Interpreter','latex')
set(findall(hfig2,'-property','TickLabelInterpreter'),'TickLabelInterpreter','latex')
set(hfig2,'Units','centimeters','Position',[3 3 picturewidth hw_ratio*picturewidth])
pos = get(hfig2,'Position');
set(hfig2,'PaperPositionMode','Auto','PaperUnits','centimeters','PaperSize',[pos(3), pos(4)])
print(hfig2,fname2,'-dpdf','-vector','-fillpage')

%% Figure 3: Vs comparison (sanity check)
hfig3 = figure; hold on

for i = 1:length(configs)
    d = data{i};
    plot(d.t, d.Vs, 'Color', colors{i}, 'LineWidth', 1.8, 'DisplayName', labels{i})
end

xlabel('time $t$ (s)')
ylabel('$V_s$ (V)')
legend('show','Location','best')
xlim([-0.5, 5])

fname3 = 'Vs_comparison_step04';
set(findall(hfig3,'-property','FontSize'),'FontSize',17)
set(findall(hfig3,'-property','Box'),'Box','off')
set(findall(hfig3,'-property','Interpreter'),'Interpreter','latex')
set(findall(hfig3,'-property','TickLabelInterpreter'),'TickLabelInterpreter','latex')
set(hfig3,'Units','centimeters','Position',[3 3 picturewidth hw_ratio*picturewidth])
pos = get(hfig3,'Position');
set(hfig3,'PaperPositionMode','Auto','PaperUnits','centimeters','PaperSize',[pos(3), pos(4)])
print(hfig3,fname3,'-dpdf','-vector','-fillpage')
