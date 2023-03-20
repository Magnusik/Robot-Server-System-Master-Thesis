function [uL,uR,distanceDriven,turning,waitingCommand] = regulator(xHat,setpoint,turning,sDistance,distanceDriven,ddInit,waitingCommand)
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
theta_0 = theta;

%setpoint
x_d = setpoint(1);
y_d = setpoint(2);

%Errors
delta_x = x_d - x;
delta_y = y_d - y;

%thresholds
angleThreshold = deg2rad(3);

maxDistanceTarget =sqrt( (x_d-ddInit(1))^2 + (y_d-ddInit(2))^2 ); 
drThreshold      = 50;
ddThreshold     = maxDistanceTarget;


distanceRemaining    = sqrt(delta_x^2+delta_y^2);
distanceDriven       = distanceDriven+sDistance;

% angle towards setpoint  
theta_target = atan2(delta_y,delta_x); 
thetaError = modulus(theta_target-theta_0+pi,2*pi)-pi; %%smallest signed angle


if turning
    u = 12;
    [uL, uR,turning]            = rotateRobot(thetaError,theta_0,angleThreshold,u);
    distanceDriven = 0;
else
    
    u = min(30,floor(10+distanceRemaining/100)); %Input slows down depending on distance remaining to target
    
    [uL, uR]                    = moveForward(thetaError,distanceRemaining,distanceDriven,drThreshold,ddThreshold,u,waitingCommand);
    if (uL == 0) && (uR == 0)
        waitingCommand = 1;
    end
end

