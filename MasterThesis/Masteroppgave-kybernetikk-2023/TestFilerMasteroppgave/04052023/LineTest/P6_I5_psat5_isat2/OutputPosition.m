fileID = fopen('P6_I5_psat5_isat2.txt','r');


tline=fgetl(fileID);
%headers = strsplit(tline,','); kan brukes for å fjerne headers (fjerner
%første linje

formatSpec = '%f%f%f%f%f%f%f%f';
datacell = textscan(fileID,formatSpec,'Delimiter',',');
time = datacell{2};
X = datacell{6};
Z = datacell{7};
Y = datacell{8};

figure(1);
hold on;
plot(X(1,1),Y(1,1),'o','MarkerSize',10);
plot(X(end,1),Y(end,1),'o','MarkerSize',10);
plot(X,Y);
grid on;
title('Position Line Test 3000 mm P = 6, I = 5');
xlabel('x [mm]');
ylabel('y [mm]');
legend('Starting point','End point','OptiTrac path');
hold off;