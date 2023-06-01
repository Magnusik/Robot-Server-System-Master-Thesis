fileID = fopen('motiveSquareTestPIDnoBug.txt','r');
fileID2 =fopen('pidSquareTest.txt','r');

axis equal
tline=fgetl(fileID);
%headers = strsplit(tline,','); kan brukes for å fjerne headers (fjerner
%første linje

formatSpec = '%f%f%f%f%f%f%f%f';
formatSpec2 = '%f%f';

datacell = textscan(fileID,formatSpec,'Delimiter',',');
datacell2 = textscan(fileID2,formatSpec2);
time = datacell{2};
X = datacell{6};
Z = datacell{7};
Y = datacell{8};

X2 = datacell2{1};
Y2 = datacell2{2};

figure(1);
hold on;
motiveOffsetX =1583;
motiveOffsetY =-171;
plot(0,0,'o','MarkerSize',5);
plot(1000,0,'o','MarkerSize',5);
plot(1000,1000,'o','MarkerSize',5);
plot(0,1000,'o','MarkerSize',5);
radius = 100;
viscircles([1000, 0], radius);
viscircles([0,1000],radius);
viscircles([1000,1000],radius)
viscircles([0, 0], radius);
plot(X+motiveOffsetX,-Y-motiveOffsetY,'-','MarkerSize',10);
plot(X2,Y2,'-','MarkerSize',10);

grid on;
title('SquareTest PID 1000mm P = 20, I = 20, D = 0.5');
xlabel('x [mm]');
ylabel('y [mm]');
legend('Starting point','Waypoint 1','Waypoint 2','Waypoint 3','OptiTrac path','Estimates');
hold off;