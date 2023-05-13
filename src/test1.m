clear;clc;close all;

delX = 1/51;
delT = 3e8/delX;
x = linspace(0,1,51);
xx = linspace(0,1,1000);
yy = sin(2.*3.141519./.3.*abs(xx-.5));

E = importdata("../build/Debug/fieldE.txt");
H = importdata("../build/Debug/fieldH.txt");

% Timestamp: 0
figure;

subplot(2,1,1);
grid on; hold on;
stem(x,E(1,:));
plot(xx,yy);
xlim([0,1]);

subplot(2,1,2);
grid on; hold on;
stem((x+delX/2),H(1,:));
xlim([0,1]);


