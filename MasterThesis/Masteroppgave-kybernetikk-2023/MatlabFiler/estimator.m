function [xHat, sDistance] = estimator(Encoder,prev,turning,sThetaGyro)
% Estimates position and orientation [x_hat, y_hat, theta_hat]
% Returns xHat
% VARIABLE   [UNITS] [RANGE]      ~  Description
% -------------------------------------------------------------------------
% Encoder   [int,int]             ~ wheel encoder ticks
% sThetaGyro[rad]                 ~ theta increment from gyroscope
% turning   [bool]                ~ is the robot in rotating mode?
% sDistance [mm]                  ~ distance travelled since last cycle
% prev      [mm,mm,rad]           ~ the previous iteration from xHat
% xHat      [mm,mm,rad]           ~ the current estimate pose [x,y,theta]
% -------------------------------------------------------------------------

%Constants  [ticks], [mm]
nTicks               = 300;
diameterWheel        = 67;
oneRevWheel          = pi*diameterWheel;
wheelRatio           = oneRevWheel/nTicks;

diameterWheelBase    = 168;
oneRevWheelBase      = pi*diameterWheelBase;

%Encoder ticks from sample, difference of tick sample and 
%average of tick
sTicksLeft          = Encoder(1);
sTicksRight         = Encoder(2);
dTicks              = sign(sTicksRight-sTicksLeft)*abs(sTicksRight-sTicksLeft)/2;
aTicks              = (sTicksLeft+sTicksRight)/2;

%Distance [mm] from one sample, Distance of ticks difference (used to calculate angle theta) 
sDistance           = aTicks*wheelRatio;
distanceTicks       = dTicks*wheelRatio;

%Theta change orientation [rad] in one sample
sTheta              = (distanceTicks/oneRevWheelBase)*2*pi;

if turning
    x = prev(1);
    y = prev(2);
    theta = prev(3)+deg2rad(sThetaGyro);
    sDistance = 0;
else
    x = prev(1) + sDistance*cos(prev(3));
    y = prev(2) + sDistance*sin(prev(3));
    theta = prev(3)+sTheta;
    
end
theta = modulus(theta+pi,2*pi)-pi; %% smallest signed angle (maps angle into [-pi,pi]
xHat = [x,y,theta];
end

