function [gX_hat,gY_hat,gTheta_hat,distanceDriven,leftU,rightU,turning,waitingCommand] = ...
    api(setpointX,setpointY,newCommand,waitingCommand,ticksLeft,ticksRight,distanceDriven,turning,xprev,yprev,thetaprev)
%changes global states and returns input to the motors
% 

setpoint = [setpointX,setpointY];
Encoder = [ticksLeft,ticksRight];

prev = [xprev,yprev,thetaprev];

[xHat, sDistance] = estimator(Encoder,prev,turning);

[uL, uR,distanceDriven,turning,waitingCommand] = regulator(xHat,setpoint,turning,sDistance,distanceDriven,waitingCommand);

gX_hat = xHat(1);
gY_hat = xHat(2);
gTheta_hat =xHat(3);

leftU  = uL;
rightU = uR;

end
