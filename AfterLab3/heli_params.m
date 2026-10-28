%% heli_params.m — helicopter-specific constants shared by all parts
init_heli_3_10;                         % provided: encoder calibration etc.

addpath('utils')

%% ---------- Physical parameters ----------
g   = 9.81;      % [m/s^2]
m_c = 1.92;      % [kg] counterweight
m_p = 0.72;      % [kg] one motor
l_c = 0.46;      % [m]  elevation axis -> counterweight
l_h = 0.66;      % [m]  elevation axis -> head
l_p = 0.175;     % [m]  pitch axis -> motor

%% ---------- Measured on the rig (Part I, Task 2) ----------
Vs0      = 7.3;  % [V]   hover voltage at e = 0
Vd_trim  = 0;    % [V]   front/back mismatch trim (fill in if you used one)
e_offset = 0;    % [rad] elevation encoder offset (fill in from your Simulink)

%% ---------- Derived: motor constant ----------
L2  = g*(m_c*l_c - 2*m_p*l_h);
K_f = -L2/(l_h*Vs0);                    % [N/V] -> 0.1368

%% ---------- Derived: inertias ----------
Jp = 2*m_p*l_p^2;                       % 0.0441
Je = m_c*l_c^2 + 2*m_p*l_h^2;           % 1.0335
Jl = m_c*l_c^2 + 2*m_p*(l_h^2 + l_p^2); % 1.0776

%% ---------- Derived: linearized model constants ----------
K1 = K_f*l_p/Jp;                        % 0.5430
K2 = K_f*l_h/Je;                        % 0.0874
K3 = K_f*l_h*Vs0/Jl;                    % 0.6117  (sign: match your prelab)

fprintf('K_f = %.4f, K1 = %.4f, K2 = %.4f, K3 = %.4f\n', K_f, K1, K2, K3);