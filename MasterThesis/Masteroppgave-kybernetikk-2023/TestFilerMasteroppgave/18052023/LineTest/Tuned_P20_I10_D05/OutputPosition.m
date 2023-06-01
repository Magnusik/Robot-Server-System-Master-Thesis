fileID = fopen('motive_P20_I10_D05.txt','r');
fileID2 =fopen('estimates_P20_I10_D05.txt');


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
motiveOffsetX =1585.7;
motiveOffsetY =-171;
plot(0,0,'o','MarkerSize',5);
plot(3000,0,'o','MarkerSize',5);
radius = 100;
viscircles([3000, 0], radius);
plot(X+motiveOffsetX,Y+motiveOffsetY);
plot(X2,-Y2);

grid on;
title('Position Line Test 3000 mm P = 5, I = 10, D=0.5');
xlabel('x [mm]');
ylabel('y [mm]');
legend('Starting point','Goal','OptiTrac path','Estimates');
hold off;