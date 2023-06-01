function [uL,uR] = moveForward(thetaError,distanceRemaining,distanceDriven,destinationZone,maxDistanceTarget,u,waitingCommand,thetaIntegralError,sTime,thetaDerivativeError)
% Moves the robot towards the target. PID controller to controll each wheel input. 
% Returns the input uL and uR to the DC motors drivers
% VARIABLE          [UNITS] [RANGE]     Description
% -------------------------------------------------------------------------
% thetaError        [rad] [-pi,pi]      ~ difference between orientation of robot and orientation towards setpoint 
% distanceRemaining   [mm]              ~ distance towards the destination
% distanceDriven      [mm]              ~ distance driven since last command
% destinationZone     [mm]              ~ radius around end destination
% maxDistanceTarget   [mm]              ~ maximal distance to travel for a command
% waitingCommand      [bool]            ~ the robot is in an idle state waiting for a new command?
% thetaIntegralError  [rad]             ~ accumulated angle deviation
% thetaDerivativeError[rad/s]           ~ theta derivative divided by loop time
% sTime               [s]               ~ sample time
% uL,uR,u             [%, %,%] [0,50]   ~ input duty cycle to left and right motor
% ----------------------------------------------------------------------------

%PID gains
kP = 20;
kI = 10;
kD = 0.5;

%PID saturation limits 
proportionalLimit   = 20;
integralLimit       = 10;
derivativeLimit     = 10;

%PID corrections with saturation
uP = min(kP * abs(thetaError),proportionalLimit);
uI = min(kI * abs(thetaIntegralError)*sTime,integralLimit);
uD = min (kD * abs(thetaDerivativeError),derivativeLimit); 

% Conditional Control Terms depending on direction
dirProportionalControlLeft  = (1-sign(thetaError))/2; % 1 if tilted left, 0 if tilted right, 0.5 if at target direction
dirIntegralControlLeft      = (1-sign(thetaIntegralError))/2;
dirDerivativeControlLeft    = (1-sign(thetaDerivativeError))/2;

dirProportionalControlRight = (1+sign(thetaError))/2;
dirIntegralControlRight     = (1+sign(thetaIntegralError))/2;
dirDerivativeControlRight   = (1+sign(thetaDerivativeError))/2;


if distanceRemaining>destinationZone && distanceDriven<maxDistanceTarget && not(waitingCommand)
   uR = u+dirProportionalControlRight*uP+dirIntegralControlRight*uI-dirDerivativeControlRight*uD;
   uL = u+dirProportionalControlLeft*uP+dirIntegralControlLeft*uI-dirDerivativeControlLeft*uD;
   uR = round(uR); % to minimize type casting error to int later
   uL = round(uL);
   % [uL,uR] must not exceed MAX value [50,50].
else
    uR = 0;
    uL = 0;
end
