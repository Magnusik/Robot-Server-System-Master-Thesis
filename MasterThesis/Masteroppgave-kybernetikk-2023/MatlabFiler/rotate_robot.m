function [uL,uR,turning] = rotate_robot(thetaError, angleThreshold, u)
% Rotates robot based on its current position and threshold for rotating
% Returns input to DC motor drivers and manipulates turning variable
% VARIABLE    [UNITS][RANGE]          ~  Description
% -------------------------------------------------------------------------
% turning           [bool]            ~ is the robot in rotating mode?
% thetaError        [rad]             ~ difference between robot orientation and orientation towards target
% angleThreshold    [rad]             ~ stop condition for rotation mode
% uL,uR,u           [%, %,%] [0,50]   ~ input duty cycle to left and right motor
% -------------------------------------------------------------------------
if abs(thetaError)>angleThreshold
    turning = 1;
    if (thetaError)>0 %% rotate counterclockwise
        uR = u;
        uL = -u;
    else %% rotate counter clockwise
        uR = -u;
        uL = u;
    end 
else
    turning = 0;
    uR = 0;
    uL = 0;
end
