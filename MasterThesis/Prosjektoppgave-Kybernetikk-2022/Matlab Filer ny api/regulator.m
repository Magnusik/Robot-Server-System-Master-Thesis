function [uL,uR,distanceDriven,turning,waitingCommand] = regulator(xHat,setpoint,turning,sDistance,distanceDriven,waitingCommand)
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
delta_x
delta_y
%thresholds
angleThreshold = deg2rad(5);
drThreshold      = 50;
ddThreshold     = 1200;


distanceRemaining    = sqrt(delta_x^2+delta_y^2);
distanceDriven       = distanceDriven+sDistance;
distanceDriven
distanceRemaining

if turning
    u = 12;
    [uL, uR,turning]            = rotateRobot(delta_x,delta_y,theta_0,angleThreshold,u);
    distanceDriven = 0;
else
    u = 10;
    [uL, uR]                    = moveForward(distanceRemaining,distanceDriven,drThreshold,ddThreshold,u,waitingCommand);
    if (uL == 0) && (uR == 0)
        waitingCommand = 1;
    end
end

