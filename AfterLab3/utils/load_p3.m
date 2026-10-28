function d = load_p3(tag)
% Usage:  d = load_p3('T2_pitch_acc_vs_enc');
% Signal groups in Mux order - edit if your Mux differs
names  = {'enc', 'gyro', 'acc', 'new', 'y', 'xhat', 'ref', 'u'};
widths = [  6      3       3      1     5     5       2      2 ];

S = load(['p3_' tag '.mat']);
f = fieldnames(S);
D = S.(f{1})';               % one column per signal
d.t = D(:,1);

col = 2;
for k = 1:numel(names)
    last = col + widths(k) - 1;
    if last <= size(D,2)
        d.(names{k}) = D(:, col:last);
    else
        d.(names{k}) = [];   % not logged yet
    end
    col = last + 1;
end

p = ['p3_' tag '_params.mat'];
if isfile(p), d.params = load(p); end
end