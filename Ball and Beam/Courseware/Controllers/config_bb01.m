%% CONFIG_BB01
%
% Sets the model variables of the Quanser BB01 plant.
%
% ************************************************************************
% Output parameters:
% L_beam    Beam length                                         (m)
% r_arm     Distance between SRV02 output gear shaft and 
%           coupled joint                                       (m)
% J_b       Moment of inertia of ball.                          (kg.m^2)
% g         Gravitational constant                              (m/s^2)
% r_b       Radius of ball                                      (m)
% m_b       Mass of ball                                        (kg)
% THETA_OFF SRV02 load angle offset.                            (rad)
% THETA_MIN Minimum SRV02 Load Angle                            (rad)
% THETA_MAX Maximum SRV02 Load Angle                            (rad)
% K_BS      Ball position sensor calibration gain               (m/V)
%
% Copyright (C) 2007 Quanser Consulting Inc.
% Quanser Consulting Inc.
%%
% 
function [ L_beam, r_arm, r_b, m_b, J_b, g, THETA_OFF, THETA_MIN, THETA_MAX, K_BS] = config_bb01( )
    % Calculate useful conversion factors
    [ K_R2D, K_D2R, K_IN2M, K_M2IN, K_RDPS2RPM, K_RPM2RDPS, K_OZ2N, K_N2OZ, K_LBS2N, K_N2LBS, K_G2MS, K_MS2G ] = calc_conversion_constants ();    
    % Beam length (m)
    L_beam = 16.75 * K_IN2M; 
    % Distance between SRV02 output gear shaft and coupled joint (m)
    r_arm = 1 * K_IN2M;
    % Gravitational constant (m/s^2)
    g = 9.81;
    % Radius of ball (m)
    r_b = 0.5 * K_IN2M;
	% Mass of ball (kg)
    m_b = 0.064;
    % Moment of inertia of ball (kg.m^2)
    J_b = 2/5 * m_b * r_b^2;
    % SRV02 Load Angle Offset to read zero when calibrated (rad)
    THETA_OFF = - 56.0 * K_D2R; 
    % Minimum SRV02 Load Angle (rad)
    THETA_MIN = - 56.0 * K_D2R;
    % Maximum SRV02 Load Angle (rad)
    THETA_MAX = 56.0 * K_D2R;
    % Ball position sensor calibration gain (m/V)
    K_BS = - L_beam / 10;
end