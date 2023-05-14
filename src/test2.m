clear;clc;close all;

N=100;
t_max = 300;

delX = 1/N;
delT = 3e8/delX;
xE = linspace(0,1,N);
xH = xE(1:end-1);
xH = xH + delX/2;
xx = linspace(0,1,1000);
yy = sin(2.*3.141519./.3.*abs(xx-.5));

E = importdata("./fieldE.txt");
H = importdata("./fieldH.txt");

% Movie
M=moviein(t_max);

for t = 1:25:t_max
    figure; 

    subplot(2,1,1);
    plot(xE,E(t,:),"r");
    grid on;
    ylabel("E_z");
    xlabel("Time");
    ylim([-2,2]);
    xlim([0 1]);

    subplot(2,1,2);
    plot(xH,H(t,:),"b");
    grid on;
    ylabel("H_y");
    xlabel("Time");
    ylim([-2,2]);
    xlim([0 1]);
    
end
% v = VideoWriter('newfile.avi');
% open(v);
% writeVideo(v,M)
% close(v)
% movie(M,1);