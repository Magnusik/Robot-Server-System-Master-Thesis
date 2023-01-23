fileID = fopen('manual20cm.txt','r');
formatSpec = '%f %f';

sizeA = [3 Inf];
sizeB = [3 Inf];

A = fscanf(fileID,formatSpec,sizeA);

figure(1);
hold on;
title('Position (x,y) by manually maneuvering robot 20 cm with estimator');
h = plot(A(1,:),A(2,:));
set(h,'Marker','square')
xlabel('x estimate [mm]');
ylabel('y estimate [mm]');
grid on;
hold off;

figure(2);
hold on;
title('Theta by manually maneuverying robot 20 cm with estimator');
xlabel('Sample');
ylabel('Theta estimate [degrees]');
h = plot(A(3,:));
set(h,'Marker','square')
grid on;
hold off;
