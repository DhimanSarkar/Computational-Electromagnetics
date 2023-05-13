clear;clc;

N=100;
t_max = 300;

delX = 1/N;
delT = 3e8/delX;
xE = linspace(0,1,N);
xH = xE(1:end-1);
xH = xH + delX/2;
xx = linspace(0,1,1000);
yy = sin(2.*3.141519./.3.*abs(xx-.5));

E = importdata("../build/Debug/fieldE.txt");
H = importdata("../build/Debug/fieldH.txt");

% Movie
M=moviein(t_max);

for t = 1:t_max
    plot3(0*xE,xE,E(t,:));
    hold on;
    plot3(H(t,:),xH,0*xH);
    hold off;
    grid on;
    xlabel("H_y");
    ylabel("Time");
    zlabel("E_x");
    zlim([-2 2]);
    xlim([-2,2]);
    ylim([0 1]);
    M(:,t) = getframe();
    
end
v = VideoWriter('newfile.avi');
open(v);
writeVideo(v,M)
close(v)
movie(M,1);