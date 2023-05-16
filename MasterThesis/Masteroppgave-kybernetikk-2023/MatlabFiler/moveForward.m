function [uL,uR] = moveForward(thetaError,distanceRemaining,distanceDriven,thresholdDR,thresholdDD,u,waitingCommand,thetaIntegralError,delta_t,thetaDerivativeError,distanceDrivenPrev)
%Moves the robot Forward if thresholds are met
%  distanceRemaining [mm]
%  distanceDriven [mm]
%  thresholdDR [mm]
%  thresholdDD [mm]

%% PID REG Input [thetaError,thetaIntegralError,thetaDerivativeError] Output [uL, uR] PID regulator (MIMO PID)

%PID gains
k_p = 20;
k_i = 10;
k_d = 0.5;

%PID saturation limits 
p_lim = 20;
i_lim = 10;
d_lim = 10;

%PID corrections with saturation
u_p = min(k_p * abs(thetaError),p_lim);
u_i = min(k_i * abs(thetaIntegralError)*delta_t,i_lim);
u_d = min (k_d * abs(thetaDerivativeError),d_lim); 

% Conditional Control Terms depending on direction
dirProportionalControlLeft  = (1-sign(thetaError))/2; % 1 if tilted left, 0 if tilted right, 0.5 if at target direction
dirIntegralControlLeft      = (1-sign(thetaIntegralError))/2;
dirDerivativeControlLeft    = (1-sign(thetaDerivativeError))/2;

dirProportionalControlRight = (1+sign(thetaError))/2;
dirIntegralControlRight     = (1+sign(thetaIntegralError))/2;
dirDerivativeControlRight   = (1+sign(thetaDerivativeError))/2;


if distanceRemaining>thresholdDR && distanceDriven<thresholdDD && not(waitingCommand)
   uR = u+dirProportionalControlRight*u_p+dirIntegralControlRight*u_i-dirDerivativeControlRight*u_d;
   uL = u+dirProportionalControlLeft*u_p+dirIntegralControlLeft*u_i-dirDerivativeControlLeft*u_d;
   uR = round(uR); % to minimize type casting error to int later
   uL = round(uL);
   % [uL,uR] must not exceed MAX value [50,50].
else
    uR = 0;
    uL = 0;
end
