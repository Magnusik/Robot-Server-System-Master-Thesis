fileID = fopen('lineTest1000_16_03.txt','r');


tline=fgetl(fileID);
%headers = strsplit(tline,','); kan brukes for å fjerne headers (fjerner
%første linje

formatSpec = '%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f';
datacell = textscan(fileID,formatSpec,'Delimiter',',');
time = datacell{2};
X = datacell{18};
Z = datacell{19};
Y = datacell{20};

figure(1);
hold on;
plot(X(1,1),Y(1,1),'o','MarkerSize',10);
plot(X(end,1),Y(end,1),'o','MarkerSize',10);
plot(X,Y);
grid on;
title('Position Line Test 1000 mm');
xlabel('x [mm]');
ylabel('y [mm]');
legend('Starting point','End point','OptiTrac path');
hold off;