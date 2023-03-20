function [uL,uR] = moveForward(thetaError,distanceRemaining,distanceDriven,thresholdDR,thresholdDD,u,waitingCommand)
%Moves the robot Forward if thresholds are met
%  distanceRemaining [mm]
%  distanceDriven [mm]
%  thresholdDR [mm]
%  thresholdDD [mm]

k_p = 0.75;
% k_i = 0.5;
% k_d = 0.5;

%thetaIntegralError = thetaIntegralError+thetaError; %% must be 

%pidU = k_p*thetaError+k_i*thetaIntegralError+k_d*thetaErrorDot;

if distanceRemaining>thresholdDR && distanceDriven<thresholdDD && not(waitingCommand)
    uR = u+1+k_p*thetaError;
    uL = u-k_p*thetaError;
    
else
    uR = 0;
    uL = 0;
end

