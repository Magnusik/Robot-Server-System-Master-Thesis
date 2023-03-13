clear;
xHat= [0,0,0];
setpoint = [100,100];
turning = 1;
sDistance = 100;



[uL,uR] = regulator(xHat,setpoint,turning,sDistance)