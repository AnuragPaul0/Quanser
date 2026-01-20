%% D_BB01_PD
%
% Designs a PD compensator to control the ball position on the Quanser
% BB01 plant using the root locus technique. Thus the zero location
% and the compensator gain required to satisfy the natural frequency and
% damping ratio specified are calculated. This also includes satisfying the
% desired filter cutoff frequency in the case of the Practical PD design.
%
% ************************************************************************
% Input parameters:
% K_bb      BB01 Model gain                                 (m/s^2/rad)
% wn        Natural frequency                               (rad/s)
% zeta      Damping ratio
% wf        Filter cutoff frequency                         (rad/s)
% pd_type   Selects between Ideal and Practical PD control.
% plot_rl   Plot root-locus? 
%
% ************************************************************************
% Output parameters:
% z         PD compensator zero location                        (rad/s)
% Kc        PD compensator gain                                 (rad/m)
%
% Copyright (C) 2007 Quanser Consulting Inc.
% Quanser Consulting Inc.
%
%%
function [ Kc, z ] = d_bb01_pd(K_bb, wn, zeta, wf, pd_type, plot_rl)
% BB01 Plant: X(s) / Theta_l(s)
P_bb = tf( [K_bb], [1 0 0]);
%
%% Ideal PD design
if ( pd_type == 0 )
    % Default cutoff frequency (rad/s)
    wf = 2 * pi * 2.5;
    % Compensator Gain (rad/m)
    Kc = 2*zeta*wn / K_bb;
    % Zero location (rad/s)
    z = wn^2 / K_bb / Kc;
    % Ideal PD Compensator
    C_bb = tf([1 z],[1]);
    %
%% Practical PD design
elseif ( pd_type  == 1 )
    % Resulting pole decay (s)
    Tp = 1 / ( wf - 2*zeta*wn );
    % Zero location (rad/s)
    z = wn*wf/(-wn+wf*wn*Tp+2*wf*zeta);
    % Compensator Gain (rad/m)
    Kc = wn^2 / (Tp*K_bb*z*wf);
    % Practical PD Compensator
    C_bb = tf([z+wf z*wf],[1 wf]);
end
%
%% Root Locus
% Loop transfer function
L_bb = series( C_bb, P_bb );
%
if ( plot_rl == 1 )
    % Root locus of BB01
    figure(1);
    rlocus(P_bb);
    sgrid(zeta, wn);
    axis([-10 2 -2 2]);
    % Root locus of compensator
    figure(2);
    rlocus(C_bb);
    sgrid(zeta, wn);
    axis([-10 2 -2 2]);    
    % Root locus of forward path
    figure(3);
    rlocusplot(L_bb);
    sgrid(zeta, wn);
    axis([-10 2 -2 2]);
end