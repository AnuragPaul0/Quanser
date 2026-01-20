%% D_BB01_MODEL_PARAM
%
% Calculates the BB01 model gain K_bb.
%
% ************************************************************************
% Input parameters:
% r_arm     Distance between SRV02 output gear shaft and 
%           coupled joint                                       (m)
% L_beam    Beam length                                         (m)
% r_b       Radius of ball                                      (m)
% m_b       Mass of ball                                        (kg)
% J_b       Moment of inertia of ball.                          (kg.m^2)
% g         Gravitational constant                              (m/s^2)
%
% ************************************************************************
% Output paramters:
% K_bb      Model gain                                          (m/s^2/rad)
%
% Copyright (C) 2007 Quanser Consulting Inc.
% Quanser Consulting Inc.
%%
%
function [ K_bb ] = d_bb01_model_param(r_arm, L_beam, r_b, m_b, J_b, g)
    % Model gain (m/s^2/rad)
    K_bb = m_b * g * r_arm / L_beam * r_b^2 / ( m_b * r_b^2 + J_b );
end
