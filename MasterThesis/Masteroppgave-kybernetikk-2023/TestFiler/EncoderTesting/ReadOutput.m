clear;

fileID = fopen('manuell20cm.txt','r');
fileID2 = fopen('manuell90grader.txt','r');

formatSpec = '%f %f';
formatSpec2 = '%f %f';
sizeA = [2 Inf];
sizeB = [2 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);

figure(1);
title('Manual maneuvering 20 cm');
hold on;
plot(A(1,:),A(2,:));
xlabel('Left Encoder');
ylabel('Right Encoder');
grid on;
hold off;

figure(2);
title('Manual maneuvering 90 degrees');
hold on;
plot(B(1,:),B(2,:));
xlabel('Left Encoder');
ylabel('Right Encoder');
hold on;
grid on;
plot(x2,y2);
hold off;