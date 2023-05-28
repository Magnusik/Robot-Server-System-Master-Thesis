function [uL,uR,turning] = rotateRobot(thetaError,theta_0, angleThreshold, u)
%Rotates robot based on its current position and threshold for rotating
% delta_x  = x_d - x 
% delta_y  = y_d - y
% theta_0 = theta_hat 


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
