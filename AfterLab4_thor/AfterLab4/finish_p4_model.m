function finish_p4_model(mdl_in, mdl_out)
% FINISH_P4_MODEL  Connect the remaining root-level wiring in heli_p4_kalman.slx
%                  (version from 2 Nov, where the "Kalman Filter" subsystem is done).
%   finish_p4_model                                   % -> heli_p4_kalman_kf.slx
%   finish_p4_model('heli_p4_kalman', 'heli_p4_kalman_kf')
%
% Run p4_kalman.m first. The original file is not modified.
%
%   1. Mux3 = [Vs~; Vd~]          -> Kalman Filter in 2 (u)          [was unconnected]
%   2. Kalman x_hat               -> Demux (6 outputs) -> LQR        [was unconnected]
%   3. Kalman x_hat               -> logging Mux1 in 6                [was unconnected]
%   4. Kalman P_diag              -> logging Mux1 in 9 (new)
%   5. logged new_data taken AFTER the manual switch (Mux1 in 4)
%   6. x_hat as 3rd input on the five "*_imu v *" scopes
%   7. To File p3Run.mat -> p4Run.mat
%   8. Manual switches: reference profile <-> joystick (evaluation requirement)
if nargin < 1, mdl_in  = 'heli_p4_kalman';    end
if nargin < 2, mdl_out = 'heli_p4_kalman_kf'; end

load_system(mdl_in);
r = mdl_in;

kf    = blk(r, 'Kalman Filter');
mux3  = blk(r, 'Mux3');
demux = blk(r, 'Demux');
mux1  = blk(r, 'Mux1');
msw   = blk(r, 'Manual Switch');
dtc   = blk(r, 'Data Type Conversion');
dmx1  = blk(r, 'Demux1');
lqr   = blk(r, 'LQR controller');
joy   = blk(r, 'Joystick');

remove_dangling(r);

% 1. u into the filter
connect(r, mux3, 1, kf, 2);

% 2. x_hat -> Demux -> controller (Demux 1,2,4 already go to LQR in 2,3,5)
set_param(demux, 'Outputs', '6');
connect(r, kf, 1, demux, 1);
connect(r, demux, 3, lqr, 4);                      % e~ (only used for scope)
for k = [5 6]                                      % lambda, lambdadot unused
    t = add_term(r, demux, k);
    connect(r, demux, k, t, 1);
end

% 3./4. logging
set_param(mux1, 'Inputs', '9');
connect(r, kf, 1, mux1, 6);
connect(r, kf, 2, mux1, 9);

% 5. log new_data after the switch
ph = get_param(mux1, 'PortHandles');
l  = get_param(ph.Inport(4), 'Line');
if l ~= -1 && get_param(l, 'SrcBlockHandle') == dtc
    delete_line(r, 'Data Type Conversion/1', 'Mux1/4');
end
connect(r, msw, 1, mux1, 4);

% 6. scopes: raw IMU / encoder / Kalman
scopes = {'p_imu v p', 1; 'pdot_imu v pdot', 2; 'e_imu v e', 3; ...
          'edot_imu v edot', 4; 'lambdadot_imu v lambdadot', 6};
for i = 1:size(scopes, 1)
    sc = blk(r, scopes{i,1});
    set_param(sc, 'NumInputPorts', '3');
    connect(r, demux, scopes{i,2}, sc, 3);
end

% 7. log file name (matches save_run_p4 / load_run_p4)
set_param(blk(r, 'To File'), 'Filename', 'p4Run.mat');

% 8. reference profile (up) <-> joystick (down)
pos = get_param(dmx1, 'Position');
refs = {'Ref p_c', 1, 1, 1; 'Ref edot_c', 2, 2, 7};   % name, Demux1 out, joystick out, LQR in
for i = 1:2
    nm = refs{i,1};
    sw = blk(r, nm, false);
    if isempty(sw)
        sw = add_block('simulink/Signal Routing/Manual Switch', [r '/' nm], ...
            'Position', [pos(3)+40, pos(2)+(i-1)*60, pos(3)+70, pos(2)+(i-1)*60+30]);
    end
    lp = get_param(lqr, 'PortHandles');
    l  = get_param(lp.Inport(refs{i,4}), 'Line');
    if l ~= -1 && get_param(l, 'SrcBlockHandle') == dmx1
        delete_line(r, sprintf('Demux1/%d', refs{i,2}), sprintf('LQR controller/%d', refs{i,4}));
    end
    connect(r, dmx1, refs{i,2}, sw, 1);
    connect(r, joy,  refs{i,3}, sw, 2);
    connect(r, sw, 1, lqr, refs{i,4});
end

save_system(r, mdl_out);
fprintf('Saved as %s.slx\n', mdl_out);
try
    set_param(mdl_out, 'SimulationCommand', 'update');
    fprintf('Update diagram (Ctrl+D) OK\n');
catch err
    fprintf(2, 'Update diagram reported:\n%s\n(Did you run p4_kalman.m first?)\n', err.message);
end
open_system(mdl_out);
end

%% ======================= helpers =======================
function h = blk(sys, name, must_exist)
if nargin < 3, must_exist = true; end
h = find_system(sys, 'SearchDepth', 1, 'FindAll', 'on', 'LookUnderMasks', 'all', ...
                'FollowLinks', 'on', 'Type', 'block', 'Name', name);
h = h(arrayfun(@(x) strcmp(get_param(x, 'Parent'), getfullname(sys)), h));
if isempty(h)
    if must_exist, error('Block "%s" not found in %s', name, sys); end
    h = [];
else
    h = h(1);
end
end

function t = add_term(sys, src, port)
nm = sprintf('Term_demux_%d', port);
t  = blk(sys, nm, false);
if isempty(t)
    p = get_param(src, 'Position');
    t = add_block('simulink/Sinks/Terminator', [sys '/' nm], ...
        'Position', [p(3)+60, p(2)+20*port, p(3)+75, p(2)+20*port+15]);
end
end

function connect(sys, src, sp, dst, dp)
ps = get_param(src, 'PortHandles');
pd = get_param(dst, 'PortHandles');
l  = get_param(pd.Inport(dp), 'Line');
if l ~= -1
    if get_param(l, 'SrcPortHandle') == ps.Outport(sp), return; end
    error('%s input %d is already connected to something else', getfullname(dst), dp);
end
add_line(sys, ps.Outport(sp), pd.Inport(dp), 'autorouting', 'on');
end

function remove_dangling(sys)
L = find_system(sys, 'SearchDepth', 1, 'FindAll', 'on', 'Type', 'line');
for l = L.'
    if ~ishandle(l), continue; end
    if get_param(l, 'SrcBlockHandle') == -1 || all(get_param(l, 'DstBlockHandle') == -1)
        delete_line(l);
    end
end
end
