fileID = fopen('squaretest.txt','r');
fileID2 = fopen('squaretest2.txt','r');

formatSpec = '%f %f';
formatSpec2 = '%f %f';

sizeA = [2 Inf];
sizeB = [2 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);

figure(1);
hold on;
title('Position Square Test 1 Estimate');
xlabel('x estimate [mm]');
ylabel('y estimate [mm]');
h = plot(A(1,:),A(2,:));
set(h,'Marker','square');
grid on;
x = [0,300,300,0,0];
y = [0,0,300,300,0];
h = plot(x,y);
set(h,'Marker','square');
legend('estimate','commanded waypoints (corners)');
hold off;

figure(2);
hold on;
title('Position Square Test 2 Estimate');
xlabel('x estimate [mm]');
ylabel('y estimate [mm]');
h = plot(B(1,:),B(2,:));
set(h,'Marker','square');
grid on;
h = plot(x,y);
set(h,'Marker','square');
legend('estimate','commanded waypoints (corners)');
hold off;