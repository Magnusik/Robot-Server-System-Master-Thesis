clear;

fileID = fopen('IMUgyro.txt','r');
fileID2 = fopen('IMUaccel.txt','r');

formatSpec =  '%f %f %f';
formatSpec2 = '%f %f %f';
sizeA = [3 Inf];
sizeB = [3 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);

figure(1);
title('IMU Gyro output x, y, z while standing still');
hold on;
plot(A(1,:));
plot(A(2,:));
plot(A(3,:));
xlabel('Sample');
ylabel('Value');
legend('x','y','z')
grid on;
hold off;

figure(2);
title('IMU accelerometer x,y,z while standing still');
hold on;
plot(B(1,:));
plot(B(2,:));
plot(B(3,:));
xlabel('Sample');
ylabel('Value');
legend('x','y','z')
hold on;
grid on;
hold off;