
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
    setpointX = 10;
    setpointY = 10;
    newCommand = 0;
    ticksRight = 100;
    ticksLeft = 100;
    xprev = 10;
    yprev = 10;
    thetaprev =0;
    distanceDriven =0;
    waitingCommand =0;




[gX_hat,gY_hat,gTheta_hat,distanceDriven,leftU,rightU,turning,waitingCommand] = ...
    api(setpointX,setpointY,newCommand,waitingCommand,ticksLeft,ticksRight,distanceDriven,turning,xprev,yprev,thetaprev);