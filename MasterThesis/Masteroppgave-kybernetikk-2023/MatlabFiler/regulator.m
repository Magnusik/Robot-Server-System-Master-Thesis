function [uL,uR,distanceDriven,turning,waitingCommand,thetaIntegralError,thetaError] = regulator(xHat,setpoint,turning,sDistance,distanceDriven,ddInit,waitingCommand,thetaIntegralError,delta_t,thetaError)
%Returns the inputs to the Left and Right motors
% xHat = [x_hat, y_hat, theta_hat] ~ [mm,mm,rad]
% setpoint = [x_d, y_d] ~ [mm,mm]
% turning ~ is the robot in rotating mode?
% sDistance ~ distance moved this sample
% waitingCommand ~ the robot is in an idle state waiting for a new command


%Unpacking arguments

%xHAt
x           = xHat(1);
y           = xHat(2);
theta       = xHat(3);
theta_0     = theta;

%setpoint
x_d = setpoint(1);
y_d = setpoint(2);

%Difference in posistion towards the target 
delta_x = x_d - x;
delta_y = y_d - y;

%Conditional Thresholds
angleThreshold       = deg2rad(3);
maxDistanceTarget    = sqrt( (x_d-ddInit(1))^2 + (y_d-ddInit(2))^2 ); 
drThreshold          = 100;
ddThreshold          = maxDistanceTarget;
distanceRemaining    = sqrt(delta_x^2+delta_y^2);
distanceDrivenPrev   = distanceDriven;
distanceDriven       = distanceDriven+sDistance;

%Angle towards setpoint  
theta_target = atan2(delta_y,delta_x);

%Proportional Error
thetaErrorPrev = thetaError;
thetaError = modulus(theta_target-theta_0+pi,2*pi)-pi; %%smallest signed angle
rad2deg(thetaError)

%Derivative Error
thetaDerivativeError = (thetaError -thetaErrorPrev)/delta_t;

%Integral Error
thetaIntegralError=min(thetaIntegralError+thetaError,deg2rad(20)); % saturation of integralerror to +-20 degrees
thetaIntegralError=max(thetaIntegralError,deg2rad(-20)); 


if turning
    u = 12;
    [uL, uR,turning]            = rotateRobot(thetaError,theta_0,angleThreshold,u);
    distanceDriven = 0;
else
    u = min(30,(10+distanceRemaining/200)); %Input slows down depending on distance remaining to target
    [uL, uR]                    = moveForward(thetaError,distanceRemaining,distanceDriven,drThreshold,ddThreshold,u,waitingCommand,thetaIntegralError,delta_t,thetaDerivativeError,distanceDrivenPrev);
    if (uL == 0) && (uR == 0) % Needed to idle the robot
        waitingCommand = 1;
    end
end