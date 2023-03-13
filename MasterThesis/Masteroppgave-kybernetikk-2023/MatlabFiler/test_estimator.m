EncoderLeft    = 100;
EncoderRight  = 100;

Encoder = [EncoderLeft,EncoderRight];
turning = false;

x = 0;
y = 0;
theta = 0;

prev = [x,y,theta];

[xHat, sDistance] = estimator(Encoder,prev,turning)

rad2deg (xHat(3))