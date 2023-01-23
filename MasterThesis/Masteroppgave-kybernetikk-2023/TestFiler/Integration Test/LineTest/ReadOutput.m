fileID = fopen('squaretest.txt','r');
fileID2 = fopen('linetest.txt','r');

formatSpec = '%f %f';
formatSpec2 = '%f %f';
sizeA = [2 Inf];
sizeB = [2 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);

figure(1);
plot(A(1,:),A(2,:));
hold on;
grid on;
x = [0,300,300,0,0];
y = [0,0,300,300,0];
plot(x,y);
hold off;

figure(2);
plot(B(1,:),B(2,:));
hold on;
grid on;
x2 = [0,1000];
y2 = [0,0];
plot(x2,y2);
hold off;