
    % Returns
    init = 0;
    gX_hat = 10;
    gY_hat = 10;
    gTheta_hat = 0;
    distanceLeft = 0;
    distanceRight = 0;
    leftU = 0;
    leftR = 0;
    turning = 1;
    
    %%input arguments
    setpointX = 1000;
    setpointY = 1000;
    newCommand = 1;
    ticksRight = 100;
    ticksLeft = 100;
    xprev = 10;
    yprev = 10;
    thetaprev =0;
    distanceDriven =0;
    waitingCommand =0;
    ddInitX =0;
    ddInitY=0;
    delta_theta_gyro=0.6;




[gX_hat,gY_hat,gTheta_hat,distanceDriven,leftU,rightU,turning,waitingCommand] = ...
    controllerApi(setpointX,setpointY,newCommand,waitingCommand,ticksLeft,ticksRight,distanceDriven,turning,xprev,yprev,thetaprev,ddInitX,ddInitY,delta_theta_gyro);