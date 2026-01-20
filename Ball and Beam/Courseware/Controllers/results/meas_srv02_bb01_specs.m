%% MEAS_SRV02_BB01_SPECS
% Plots the ball position, servo angle, and input voltage found in the
% data_x, data_theta_l, and data_vm variables. This script also finds the 
% peak time, settling time, and percentage overshoot of the saved response.
%
%% Load sample data from MAT files
% Comment these lines out if you want to use the data recently stored in
% the data_x, data_theta_l, and data_vm variables after running q_bb01_pos.mdl.
% load('sample_step_rsp_x_meas_tune1.mat');
% load('sample_step_rsp_theta_meas_tune1.mat');
% load('sample_step_rsp_vm_meas_tune1.mat');
%
%% Setup variables
% Load from variables set in workspace after running a Simulink model or
% from the previously saved response saved in the MAT files above.
t = data_x(:,1);
yd = data_x(:,2);
y = data_x(:,3);
th_d = data_theta_l(:,2);
th = data_theta_l(:,3);
u = data_vm(:,2);
%
%% Plot response
figure(4)
subplot(3,1,1);
plot(t,yd,'b:',t,y,'r-');
% axis([0 25 -10 10])
ylabel('x (cm)');
subplot(3,1,2);
plot(t,th_d,'b:',t,th,'r-');
% axis([0 25 -60 60])
ylabel('\theta_l (deg)');
subplot(3,1,3);
plot(t,u,'r-');
% axis([0 25 -12 12])
ylabel('V_m (V)');
xlabel('time (s)');
%
%% Measure Specs
% Measure the peak time, settling time, steady-state error, and percentage
% overshoot of the response.
[ tp_m, ts_m, e_ss_m, PO_m ] = meas_step_rsp_specs( t, yd, y, c_ts, 0.01 );
 
%% Display Results
disp(' ');
disp( 'Measured peak time, percentage overshoot, and steady-state error: ' )
disp( [ '     tp = ' num2str( tp_m, 3 ) ' s' ] )
disp( [ '     ts = ' num2str( ts_m, 3 ) ' s' ] )
disp( [ '     PO = ' num2str( PO_m, 3 ) ' %' ] )
disp( [ '   e_ss = ' num2str( e_ss_m, 3 ) ' cm' ] )
%