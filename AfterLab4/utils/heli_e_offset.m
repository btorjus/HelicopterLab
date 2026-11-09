function off = heli_e_offset()
% HELI_E_OFFSET  Elevation encoder offset [rad] (Part I, Task 2.1.2).
% The encoder is zeroed with the head resting on the table, so the raw
% encoder e reads +off when the arm is horizontal. Corrected: e = e_raw - off.
% Never added in Simulink, so it is applied in post-processing (loaders).
% Provisional value from data: Part IV ground (IMU) 0.383, Part III/IV flights 0.38-0.40.
% Replace with the value measured with a spirit level at the lab.
% Same value in every AfterLabN/utils copy - change all of them together.
off = 0.39;
end
