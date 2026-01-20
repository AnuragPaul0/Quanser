%% MEAS_BB01_SPECS
% Plots the ball position and servo angle found in the data_x and
% data_theta_l variables. This script also finds the peak time, settling
% tie, and percentage overshoot of the saved response.
%
%% Load sample data from MAT files
% Comment these lines out if you want to use the data recently stored in
% the data_x and data_theta_l variables from after running q_bb01_pos.mdl.
% load('sample_step_rsp_x_meas_tune1.mat');
% load('sample_step_rsp_vm_meas_tune1.mat');
%
%% Setup variables
% Load from variables set in workspace after running a Simulink model or
% from the previously saved response saved in the MAT files above.
t = data_x(:,1);
yd = data_x(:,2);
y = data_x(:,3);
u = data_theta_l(:,2);
%
%% Plot response
figure(4);
subplot(2,1,1);
plot(t,yd,'b:',t,y,'r-');
ylabel('x (cm)');
subplot(2,1,2);
plot(t,u,'r-');
ylabel('\theta_l (deg)');
xlabel('time (s)');
%
%% Measure Specs
% Measure the peak time, settling time, steady-state error, and percentage
% overshoot of the response.
[ tp_m, ts_m, e_ss_m, PO_m ] = meas_step_rsp_specs( t, yd, y, c_ts, 0.1 );
%
%% Display Results
disp(' ');
disp( 'Measured peak time, percentage overshoot, and steady-state error: ' )
disp( [ '     tp = ' num2str( tp_m, 3 ) ' s' ] );
disp( [ '     ts = ' num2str( ts_m, 3 ) ' s' ] );
disp( [ '     PO = ' num2str( PO_m, 3 ) ' %' ] );
disp( [ '   e_ss = ' num2str( e_ss_m, 3 ) ' cm' ] );
%