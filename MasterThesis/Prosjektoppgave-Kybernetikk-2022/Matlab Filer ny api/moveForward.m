function [uL,uR] = moveForward(distanceRemaining,distanceDriven,thresholdDR,thresholdDD,u,waitingCommand)
%Moves the robot Forward if thresholds are met
%  distanceRemaining [mm]
%  distanceDriven [mm]
%  thresholdDR [mm]
%  thresholdDD [mm]

if distanceRemaining>thresholdDR && distanceDriven<thresholdDD && not(waitingCommand)
    uR = u+1;
    uL = u;
else
    uR = 0;
    uL = 0;
end

