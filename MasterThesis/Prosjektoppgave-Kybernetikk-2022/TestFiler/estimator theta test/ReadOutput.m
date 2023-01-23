fileID = fopen('manualEstimatorTheta90.txt','r');
fileID2 = fopen('manualEstimatorTheta180.txt','r');

formatSpec = '%f %f';
formatSpec2 = '%f %f';
sizeA = [3 Inf];
sizeB = [3 Inf];

A = fscanf(fileID,formatSpec,sizeA);
B = fscanf(fileID2,formatSpec2,sizeB);

figure(1);
hold on;
title('Theta manual maneuvering 90 degrees with Estimator');
ylabel('Theta [degrees]');
xlabel('Sample');
h = plot(A(3,:));
set(h,'Marker','square');
grid on;
hold off;

figure(2);
hold on;
title('Theta manual maneuvering 180 degrees with Estimator');
ylabel('Theta [degrees]');
xlabel('Sample');
h = plot(B(3,:));
set(h,'Marker','square');
grid on;
hold off;