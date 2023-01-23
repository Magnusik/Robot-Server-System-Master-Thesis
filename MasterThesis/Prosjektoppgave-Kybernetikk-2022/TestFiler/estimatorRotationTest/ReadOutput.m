fileID = fopen('commanded90degree0x300y.txt','r');
formatSpec = '%f %f';

sizeA = [3 Inf];

A = fscanf(fileID,formatSpec,sizeA);

figure(1);
hold on;
title('Position commanded set point (0,300)');
xlabel('x estimate [mm]');
ylabel('y estimate [mm]');
h = plot(A(1,:),A(2,:));
set(h,'Marker','square');
grid on;
hold off;

figure(2);
hold on;
title('Theta commanded set point (0,300)');
ylabel('Theta [degrees]');
xlabel('Sample');
h = plot(A(3,:));
set(h,'Marker','square');
grid on;
hold off;
