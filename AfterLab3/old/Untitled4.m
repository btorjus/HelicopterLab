d = load_p3('Ass');      % navnet dere lagret med
figure
subplot(3,1,1); plot(d.t, d.ref(:,2), d.t, d.enc(:,6), d.t, d.xhat(:,4)); grid on
legend('\dot e_c', '\dot e enkoder', '\dot e estimat'); ylabel('rad/s')
subplot(3,1,2); plot(d.t, d.ref(:,1), d.t, d.enc(:,3)); grid on
legend('p_c', 'p enkoder'); ylabel('rad')
subplot(3,1,3); plot(d.t, d.u); grid on
legend('V_s', 'V_d'); ylabel('V'); xlabel('Tid [s]')