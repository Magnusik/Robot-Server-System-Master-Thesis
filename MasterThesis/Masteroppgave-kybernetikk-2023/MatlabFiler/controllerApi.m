function [gX_hat,gY_hat,gTheta_hat,distanceDriven,leftU,rightU,turning,waitingCommand,thetaIntegralError,thetaError] = ...
    controllerApi(setpointX,setpointY,newCommand,waitingCommand,ticksLeft,ticksRight,distanceDriven,turning,xprev,yprev,thetaprev,ddInitX,ddInitY,sThetaGyro,thetaIntegralError,delta_t,thetaError)
%changes global states and returns input to the motors
% 

setpoint = [setpointX,setpointY];
Encoder = [ticksLeft,ticksRight];
ddInit = [ddInitX, ddInitY];
prev = [xprev,yprev,thetaprev];

[xHat, sDistance] = estimator(Encoder,prev,turning,sThetaGyro);

[uL, uR,distanceDriven,turning,waitingCommand,thetaIntegralError,thetaError] = regulator(xHat,setpoint,turning,sDistance,distanceDriven,ddInit,waitingCommand,thetaIntegralError,delta_t,thetaError);

gX_hat = xHat(1);
gY_hat = xHat(2);
gTheta_hat =xHat(3);

leftU  = uL;
rightU = uR;

end
