%% D_BB01_SPECS
%
% Compute the natural frequency and damping ratio based on the settling
% time, settling percentage, and percentage overshoot specifications.
%
% ************************************************************************
% Input paramters:
% PO        Percentage overshoot specification      (%)
% ts        Settling time specifications            (s)
% c_ts      Settling time percentage                (%)
%
% ************************************************************************
% Output parameters:
% wn        Natural frequency                       (rad/s)
% zeta      Damping ratio                           
%
% Copyright (C) 2007 Quanser Consulting Inc.
% Quanser Consulting Inc.
%%
%
function [ wn, zeta ] = d_bb01_specs( PO, ts, c_ts )
    % Damping ratio from overshoot specification.
    zeta = -log(PO/100) * sqrt( 1 / ( ( log(PO/100) )^2 + pi^2 ) );    
    % Natural frequency from specifications (rad/s)
    wn = -log( c_ts * (1-zeta^2)^(1/2) ) / (zeta * ts);
end