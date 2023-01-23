clear;

fileID = fopen('manuell20cm.txt','r');
fileID2 = fopen('manuell90grader.txt','r');
fileID3 = fopen('manuellLeft1Rev.txt','r');
fileID4 = fopen('manuellRight1Rev.txt','r');

formatSpec = '%f %f';
formatSpec2 = '%f %f';
formatSpec3 = '%f %f';
formatSpec4 = '%f %f';

sizeA = [2 Inf];
sizeB = [2 Inf];
sizeC = [2 Inf];
sizeD = [2 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);
C = fscanf(fileID3,formatSpec3,sizeC);
D = fscanf(fileID4,formatSpec4,sizeD);

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
grid on;
hold off;


figure(3);
title('Manual Maneuvering one Revolution Left Encoder');
hold on;
plot(C(1,:));
xlabel('Sample');
ylabel('Left Encoder Ticks');
grid on;
hold off;

figure(4);
title('Manual Maneuvering one Revolution Right Encoder');
hold on;
plot(D(2,:));
xlabel('Sample');
ylabel('Right Encoder Ticks');
grid on;
hold off;