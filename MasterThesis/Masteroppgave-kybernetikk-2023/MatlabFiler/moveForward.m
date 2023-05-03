function [uL,uR] = moveForward(thetaError,distanceRemaining,distanceDriven,thresholdDR,thresholdDD,u,waitingCommand,thetaIntegralError,delta_t)
%Moves the robot Forward if thresholds are met
%  distanceRemaining [mm]
%  distanceDriven [mm]
%  thresholdDR [mm]
%  thresholdDD [mm]

k_p = 6;
k_i = 5;
% k_d = 0.5;


%% Single Input [thetaError] Multiple Output [uL, uR] PID regulator (SIMO PID)

%PID saturation limits
p_lim = 5;
i_lim = 2;

%PID corrections with saturation
u_p = min(k_p * abs(thetaError),p_lim);

u_i = min(k_i * abs(thetaIntegralError)*delta_t,i_lim);


% Conditional Control Terms depending on direction
dirProportionalControlLeft  = (1-sign(thetaError))/2; % 1 if tilted left, 0 if tilted right, 0.5 if at target direction
dirIntegralControlLeft      = (1-sign(thetaIntegralError))/2;
dirProportionalControlRight = (1+sign(thetaError))/2;
dirIntegralControlRight     = (1+sign(thetaIntegralError))/2;

if distanceRemaining>thresholdDR && distanceDriven<thresholdDD && not(waitingCommand)
   uR = u+1+dirProportionalControlRight*u_p+dirIntegralControlRight*u_i;
   uL = u+dirProportionalControlLeft*u_p+dirIntegralControlLeft*u_i;
   uR = round(uR); % to minimize type casting error to int later
   uL = round(uL);
else
    uR = 0;
    uL = 0;
end
