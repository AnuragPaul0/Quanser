 %% SETUP_SRV02_EXP04_BB01
%
% Sets the necessary parameters to run the SRV02 Experiment #4: Ball and
% Beam Control laboratory using the "s_bb01_pos", "s_bb01_outer_loop" and 
% "q_bb01_pos" Simulink diagrams.
% 
% Copyright (C) 2007 Quanser Consulting Inc.
%
clear
% all;
%
%% SRV02 Configuration
% External Gear Configuration: set to 'HIGH' or 'LOW'
EXT_GEAR_CONFIG = 'HIGH';
% Encoder Type: set to 'E' or 'EHR'
ENCODER_TYPE = 'E';
% Is SRV02 equipped with Tachometer? (i.e. option T): set to 'YES' or 'NO'
TACH_OPTION = 'NO';
% Type of Load: set to 'NONE', 'DISC', or 'BAR'
LOAD_TYPE = 'NONE';
% Amplifier Gain used: 
% VoltPAQ-X1 users: set K_AMP to 1 and Gain switch on amplifier to 1
% VoltPAQ-X2 users: set to K_AMP 3
K_AMP = 1;
% Amplifier Type: set to 'VoltPAQ' or 'Q3'
AMP_TYPE = 'VoltPAQ';
% Digital-to-Analog Maximum Voltage (V)
VMAX_DAC = 10;
%
%% Lab Configuration
% Type of controller: set it to 'AUTO', 'MANUAL'
CONTROL_TYPE = 'AUTO';
% CONTROL_TYPE = 'MANUAL';
% For 'AUTO' mode: set to 1 to plot root-locus.
PLOT_RL = 1; 
% For 'AUTO' mode: set to 0 for IDEAL PD and to 1 for PRACTICAL PD compensator.
PD_TYPE = 1;
%
%% Control specifications
% SRV02 Position Control specifications
if strcmp(AMP_TYPE, 'Q3')    
    % Peak time (s)
    tp_srv02 = 0.15;
    % Percentage overshoot (%)
    PO_srv02 = 10.0;
    % BB01 Position Control Specifications
    % Settling time percentage
    c_ts = 0.04;
    % Settling time (s)
    ts_bb = 3.5;
    % Percentage overshoot (%)
    PO_bb = 7.50;
else
    % Peak time (s)
    tp_srv02 = 0.15;
    % Percentage overshoot (%)
    PO_srv02 = 5.0;
    % BB01 Position Control Specifications
    % Settling time percentage
    c_ts = 0.04;
    % Settling time (s)
    ts_bb = 3.5;
    % Percentage overshoot (%)
    PO_bb = 10.0;
end
%
%% System Parameters
% Sets model variables according to the user-defined system configuration
[ Rm, kt, km, Kg, eta_g, Beq, Jm, Jeq, eta_m, K_POT, K_TACH, K_ENC, ...
    VMAX_AMP, IMAX_AMP ] = config_srv02( EXT_GEAR_CONFIG, ENCODER_TYPE, TACH_OPTION, AMP_TYPE, LOAD_TYPE );
% Load BB01 model parameters.
[ L_beam, r_arm, r_b, m_b, J_b, g, THETA_OFF, THETA_MIN, THETA_MAX, K_BS] = config_bb01( );
%
if strcmp(AMP_TYPE, 'Q3') 
    K_BS = 2 * K_BS;
end
%% Filter Parameters
% SRV02 High-pass filter in PD control used to compute velocity
% Cutoff frequency (rad/s)
wcf = 2 * pi * 50.0;
% Damping ratio
zetaf = 0.9;
% BB01 High-pass filter in PD control used to compute velocity
% Cutoff frequency (rad/s)
wf = 2 * pi * 1.0;
%
%% Calculate Control Parameters
if strcmp ( CONTROL_TYPE , 'MANUAL' )
    % Load model parameters based on SRV02 configuration.
    [ K, tau ] = d_model_param(Rm, kt, km, Kg, eta_g, Beq, Jeq, eta_m, AMP_TYPE);
    % Calculate SRV02 PV control gains given specifications.
    kp = 0;
    kv = 0;
    % Calculate SRV02+BB01 model gain.
    K_bb = 0;
    % Calculate natural frequency and damping ratio given specifications.
    wn = 0;
    zeta = 0;
    % Design BB01 compensator
    z = 1;
    Kc = 0;
    %
elseif strcmp ( CONTROL_TYPE , 'AUTO' )
    % Load model parameters based on SRV02 configuration.
    [ K, tau ] = d_model_param(Rm, kt, km, Kg, eta_g, Beq, Jeq, eta_m, AMP_TYPE);
    % Calculate SRV02 PV control gains given specifications.
    [ kp, kv ] = d_pv_design( K, tau, PO_srv02, tp_srv02, AMP_TYPE  );
    % Calculate SRV02+BB01 model gain.
    [ K_bb ] = d_bb01_model_param(r_arm, L_beam, r_b, m_b, J_b, g);
    % Calculate natural frequency and damping ratio given specifications.
    [ wn, zeta ] = d_bb01_specs( PO_bb, ts_bb, c_ts );
    % Design BB01 compensator
    [ Kc, z ] = d_bb01_pd(K_bb, wn, zeta, wf, PD_TYPE, PLOT_RL);
end
%
%% Display
disp( ' ' );
disp( 'SRV02 model parameters: ' );
if strcmp(AMP_TYPE,'Q3')
    disp( [ '   K   = ' num2str( K, 3 ) ' rad/s^2/A' ] );
else
    disp( [ '   K   = ' num2str( K, 3 ) ' rad/s/V' ] );
    disp( [ '   tau = ' num2str( tau, 3 ) ' s' ] );
end
%
disp( 'SRV02 Specifications: ' );
disp( [ '   tp = ' num2str( tp_srv02, 3 ) ' s' ] );
disp( [ '   PO = ' num2str( PO_srv02, 3 ) ' %' ] );
%
disp( 'BB01 model parameter: ' );
disp( [ '   K_bb = ' num2str( K_bb, 3 ) ' m/s^2/rad' ] );
%
disp( 'BB01 Specifications: ' );
disp( [ '   ts = ' num2str( ts_bb, 3 ) ' s' ] );
disp( [ '   PO = ' num2str( PO_bb, 3 ) ' %' ] );
%
disp( 'SRV02 PV control gains: ' );
if strcmp(AMP_TYPE,'Q3')
    disp( [ '   kp = ' num2str( kp, 3 ) ' A/rad' ] );
    disp( [ '   kv = ' num2str( kv, 3 ) ' A.s/rad' ] );
else
   disp( [ '   kp = ' num2str( kp, 3 ) ' V/rad' ] );
   disp( [ '   kv = ' num2str( kv, 3 ) ' V.s/rad' ] );
end
%
disp( 'Natural frequency and damping ratio: ' );
disp( [ '   wn   = ' num2str( wn, 3 ) ' rad/s' ] );
disp( [ '   zeta = ' num2str( zeta, 3 ) ] );
%
disp( 'BB01 PD compensator: ' );
disp( [ '   Kc = ' num2str( Kc, 3 ) ' s/m' ] );
disp( [ '   z  = ' num2str( z, 3 ) ' rad/s' ] );
disp( [ '   wf   = ' num2str( wf, 3 ) ' rad/s' ] );
%