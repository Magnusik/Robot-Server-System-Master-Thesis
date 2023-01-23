clear;
fileID = fopen('15cyclesStraight.txt','r');
fileID2 = fopen('15cyclesRot.txt','r');


formatSpec = '%f %f';
formatSpec2 = '%f %f';
sizeA = [2 Inf];
sizeB = [2 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);

figure(1);
title('Motor Move Straight 15 cycles, 15 duty');
hold on;
plot(A(1,:),A(2,:));
xlabel('Left Encoder');
ylabel('Right Encoder');
grid on;
hold off;

figure(2);
title('Motor Rotation 15 cycles, (-15 duty Left, 15 duty Right)');
hold on;
plot(B(1,:),B(2,:));
xlabel('Left Encoder');
ylabel('Right Encoder');
grid on;
hold off;