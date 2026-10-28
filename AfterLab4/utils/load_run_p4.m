function d = load_run_p4(tag)
% Usage:  d = load_run_p4('T4_test1_par');
% Same Mux order as Part III (p3Run), with xhat now 6 wide and diag(P_hat) added
% at the end. Wire the p4Run Mux in exactly this order:
%   enc(6) | gyro(3) | acc(3) | new(1) | y(5) | xhat(6) | ref(2) | u(2) | Pdiag(6)
names  = {'enc', 'gyro', 'acc', 'new', 'y', 'xhat', 'ref', 'u', 'Pdiag'};
widths = [  6      3       3      1     5     6       2      2     6    ];

d_dir = fullfile('data','p4');
S = load(fullfile(d_dir, ['p4_' tag '.mat']));
f = fieldnames(S);
D = S.(f{1})';               % one column per signal
d.t = D(:,1);

col = 2;
for k = 1:numel(names)
    last = col + widths(k) - 1;
    if last <= size(D,2)
        d.(names{k}) = D(:, col:last);
    else
        d.(names{k}) = [];   % not logged
    end
    col = last + 1;
end

p = fullfile(d_dir, ['p4_' tag '_params.mat']);
if isfile(p), d.params = load(p); end
end
