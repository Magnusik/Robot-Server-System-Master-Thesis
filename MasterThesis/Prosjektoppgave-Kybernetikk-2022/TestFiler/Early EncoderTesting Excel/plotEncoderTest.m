
clear;clc;close;

forwardRight = xlsread('TestEncoder27102022.xlsx','B5:B34');

forwardLeft  = xlsread('TestEncoder27102022.xlsx','D5:D34');

forwardPlusRotationCCWRight = xlsread('TestEncoder27102022.xlsx','F5:F34');

forwardPlusRotationCCWLeft  = xlsread('TestEncoder27102022.xlsx','H5:H34');


samples = 30;
x = 1:1:samples;

%% Key numbers

minForwardRight  = min(forwardRight);
maxForwardRight  = max(forwardRight);
meanForwardRight = mean(forwardRight);
stdForwardRight  = std(forwardRight);

minForwardLeft  = min(forwardLeft);
maxForwardLeft  = max(forwardLeft);
meanForwardLeft = mean(forwardLeft);
stdForwardLeft  = std(forwardLeft);

minFullSequenceRight  = min(forwardPlusRotationCCWRight);
maxFullSequenceRight  = max(forwardPlusRotationCCWRight);
meanFullSequenceRight = mean(forwardPlusRotationCCWRight);
stdFullSequenceRight  = std(forwardPlusRotationCCWRight);

minFullSequenceLeft   = min(forwardPlusRotationCCWLeft);
maxFullSequenceLeft   = max(forwardPlusRotationCCWLeft);
meanFullSequenceLeft  = mean(forwardPlusRotationCCWLeft);
stdFullSequenceLeft   = std(forwardPlusRotationCCWLeft);


%% Forward 10 Cycles Right Encoder Plot

figure(1)
plot(x,forwardRight);
grid on;
grid minor;
ylabel('Encoder Ticks');
xlabel('Sample Number');
title('Forward Movement 10 Cycles Right Encoder');
hold off;

%% Forward 10 Cycles Left Encoder Plot

figure(2)
plot(x,forwardLeft);
grid on;
grid minor;
ylabel('Encoder Ticks');
xlabel('Sample Number');
title('Forward movement 10 cycles Left Encoder');
hold off;


%% Forward 10 Cycles Left Encoder Plot

figure(2)
plot(x,forwardLeft);
grid on;
grid minor;
ylabel('Encoder Ticks');
xlabel('Sample Number');
title('Forward movement 10 Cycles Left Encoder');
hold off;

%% Forward 10 Cycles and Rotation CCW 5 Cycles Right Encoder Plot

figure(3)
plot(x,forwardPlusRotationCCWRight);
grid on;
grid minor;
ylabel('Encoder Ticks');
xlabel('Sample Number');
title('Forward 10 Cycles and Rotation CCW 5 Cycles Right Encoder');
hold off;

%% Forward 10 Cycles abs(difference) Right and Left Encoder

figure(4)
plot(x,abs(forwardRight-forwardLeft));
grid on;
grid minor;
ylabel('Encoder Ticks');
xlabel('Sample Number');
title('Forward 10 Cycles Right and Left Encoder abs(difference)');
hold off;

%% Normal distribution 10 cycles Forward Right Encoder

figure(5)

R_observation = [minForwardRight:1:maxForwardRight];
R_normal = normpdf(R_observation,meanForwardRight,stdForwardRight);

L_observation = [minForwardLeft:0.1:maxForwardLeft];
L_normal = normpdf(L_observation,meanForwardLeft,stdForwardLeft);


plot(L_observation,L_normal);
hold on;
plot(R_observation,R_normal);
%pdf_ForwardRight = normpdf(observation,meanForwardRight,stdForwardRight);

grid on;
grid minor;
ylabel('Probability Density');
xlabel('Observation');
title('Normal Distribution Forward 10 Cycles Right Encoder');
hold off;


%% histograms
nbins = 30;
figure(6)
grid on;
grid minor;
histogram(forwardRight,nbins)
curtick = get(gca, 'yTick');
yticks(unique(round(curtick)));
grid on;
grid minor;
figure(7)
histogram(forwardLeft,nbins)
curtick = get(gca, 'yTick');
yticks(unique(round(curtick)));
grid on;
grid minor;
figure(8)
histogram(forwardPlusRotationCCWRight,nbins)
curtick = get(gca, 'yTick');
yticks(unique(round(curtick)));
grid on;
grid minor;
figure(9)
histogram(forwardPlusRotationCCWLeft,nbins)
curtick = get(gca, 'yTick');
yticks(unique(round(curtick)));
grid on;
grid minor;


