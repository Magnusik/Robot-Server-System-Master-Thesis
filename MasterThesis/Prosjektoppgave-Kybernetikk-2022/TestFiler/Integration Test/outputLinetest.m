clear;

fileID = fopen('LineTest.txt','r');

formatSpec =  '%f %f %f';
sizeA = [3 Inf];

A = fscanf(fileID,formatSpec,sizeA);

figure(1);
hold on;
title('Position Line Test with estimator 1000 mm');
h = plot(A(1,:),A(2,:));
set(h,'Marker','square');
xlabel('x estimate [mm]');
ylabel('y estimate [mm]');
grid on;
hold off;

figure(2);
hold on;
title('Theta Line Test with estimator 1000 mm');
hold on;
h = plot(A(3,:));
set(h,'Marker','square');
xlabel('Sample');
ylabel('Theta [degrees]');
grid on;
hold off;