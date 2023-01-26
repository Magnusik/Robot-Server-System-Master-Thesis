function [uL,uR] = moveForward(thetaError,distanceRemaining,distanceDriven,thresholdDR,thresholdDD,u,waitingCommand)
%Moves the robot Forward if thresholds are met
%  distanceRemaining [mm]
%  distanceDriven [mm]
%  thresholdDR [mm]
%  thresholdDD [mm]

if distanceRemaining>thresholdDR && distanceDriven<thresholdDD && not(waitingCommand)
    uR = u+1;
    uL = u;
    if thetaError>deg2rad(5) %% tilt counter clockwise
        uR = u+2;
        uL = u-1;
    elseif thetaError<deg2rad(-5) %% tilt clockwise
        uR = u;
        uL = u;
    end
else
    uR = 0;
    uL = 0;
end

