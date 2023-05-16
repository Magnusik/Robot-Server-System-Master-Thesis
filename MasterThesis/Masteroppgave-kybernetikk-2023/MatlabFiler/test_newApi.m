
    % Returns
    init = 1;
    gX_hat = 0;
    gY_hat = 100;
    gTheta_hat = 0;
    distanceLeft = 100;
    distanceRight = 100;
    leftU = 0;
    leftR = 0;
    turning = 0;
    
    %%input arguments
    setpointX = 3000;
    setpointY = 0;
    newCommand = 1;
    ticksRight = 100;
    ticksLeft = 100;
    xprev = 10;
    yprev = 10;
    thetaprev =pi/8;
    distanceDriven =100;
    waitingCommand =0;
    ddInitX =0;
    ddInitY=0;
    delta_theta_gyro=0.6;
    thetaIntegralError=deg2rad(30);
    delta_t = 0.2;
    thetaError = 0.2;




[gX_hat,gY_hat,gTheta_hat,distanceDriven,leftU,rightU,turning,waitingCommand] = ...
    controllerApi(setpointX,setpointY,newCommand,waitingCommand,ticksLeft,ticksRight,distanceDriven,turning,xprev,yprev,thetaprev,ddInitX,ddInitY,delta_theta_gyro,thetaIntegralError,delta_t,thetaError);