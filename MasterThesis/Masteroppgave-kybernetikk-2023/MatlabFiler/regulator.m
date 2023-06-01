function [uL,uR,distanceDriven,turning,waitingCommand,thetaIntegralError,thetaError] = regulator(xHat,setpoint,turning,sDistance,distanceDriven,ddInit,waitingCommand,thetaIntegralError,sTime,thetaError,newCommand)
%Returns the inputs to the Left and Right motors
% VARIABLE          [UNITS] [RANGE]   Description
% -------------------------------------------------------------------------
% xHat              [mm,mm,rad]       = [xEstimateNow, yEstimateNow, thetaEstimateNow]  
% setpoint          [mm,mm]           = [xSetpoint, ySetpoint]
% ddInit            [mm,mm]           = [ddInitX, ddInitY] ~ the position estimate at the time of receiving set point command
% turning           [bool]            ~ is the robot in rotating mode?
% waitingCommand    [bool]            ~ the robot is in an idle state waiting for a new command?
% sDistance         [mm]              ~ distance moved this sample  
% sTime             [s]               ~ sample time this cycle 
% xDiffTarget       [mm]              ~ difference between setpoint x and current x position estimate   
% yDiffTarget       [mm]              ~ difference between setpoint y and current y position estimate  
% thetaError        [rad] [-pi,pi]    ~ difference between orientation of robot and orientation towards setpoint 
% distanceDriven    [mm]              ~ distance driven since last setpoint command
% distanceRemaining [mm]              ~ distance from current position towards target
% maxDistanceTarget [mm]              ~ max distance to travel before stopping  
% destinationZone   [mm]              ~ radius around end destination
% angleThreshold    [rad]             ~ stop condition for rotation mode
% uL,uR             [%, %] [0,50]     ~ input duty cycle to left and right motor
% -------------------------------------------------------------------------
%xHAt
xEstimateNow           = xHat(1);
yEstimateNow           = xHat(2);
thetaEstimateNow       = xHat(3);

%Setpoint positions
xSetpoint = setpoint(1);
ySetpoint = setpoint(2);

%Difference in posistion towards the target 
xDiffTarget = xSetpoint - xEstimateNow;
yDiffTarget = ySetpoint - yEstimateNow;

%Conditional Thresholds
angleThreshold       = deg2rad(3);
maxDistanceTarget    = sqrt( (xSetpoint-ddInit(1))^2 + (ySetpoint-ddInit(2))^2 ); 
destinationZone      = 100;
distanceRemaining    = sqrt(xDiffTarget^2+yDiffTarget^2);
distanceDriven       = distanceDriven+sDistance;

%Angle towards target  
thetaSetpoint = atan2(yDiffTarget,xDiffTarget);

%Proportional Error
thetaErrorPrev = thetaError;

thetaError = modulus(thetaSetpoint-thetaEstimateNow+pi,2*pi)-pi; %%smallest signed angle
rad2deg(thetaError)

%Derivative Error
thetaDerivativeError = (thetaError -thetaErrorPrev)/sTime;
if newCommand
    thetaDerivativeError = 0; % To prevent a unintended high contribution from derivative term after rotation.
end

%Integral Error
thetaIntegralError=min(thetaIntegralError+thetaError,deg2rad(20)); % saturation of integralerror to +-20 degrees
thetaIntegralError=max(thetaIntegralError,deg2rad(-20));

if turning
    u = 12;
    [uL, uR,turning] = rotateRobot(thetaError,thetaEstimateNow,angleThreshold,u);
    distanceDriven = 0;
else
    u = min(30,(10+distanceRemaining/200)); %Input slows down depending on distance remaining to target
    [uL, uR] = moveForward(thetaError,distanceRemaining,distanceDriven,destinationZone,maxDistanceTarget,u,waitingCommand,thetaIntegralError,sTime,thetaDerivativeError);
    if (uL == 0) && (uR == 0) % Needed to idle the robot
        waitingCommand = 1;
    end
end