function [uL,uR,turning] = rotateRobot(delta_x,delta_y,theta_0, angleThreshold, u)
%Rotates robot based on its current position and threshold for rotating
% delta_x  = x_d - x 
% delta_y  = y_d - y
% theta_0 = theta_hat 

% angle towards setpoint  
theta_target = atan2(delta_y,delta_x); 
testThetaDegrees = rad2deg(theta_target)

thetaError = modulus(theta_target-theta_0+pi,2*pi)-pi; %%smallest signed angle

if abs(thetaError)>angleThreshold
    turning = 1;
    if (thetaError)>0 %% rotate counterclockwise
        uR = u;
        uL = -u;
    else %% rotate counter clockwise
        uR = -u;
        uL = u;
    end 
else
    turning = 0;
    uR = 0;
    uL = 0;
end

