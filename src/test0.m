clear;clc;

L=41;
k=2*pi/3;
x = linspace(-10,10,L);
xx = -10:.1:10;

y = sin(k*abs(x)) .* rectangularPulse(-2*pi/k,2*pi/k,x);
yy= sin(k*abs(xx)) .* rectangularPulse(-2*pi/k,2*pi/k,xx) ;

subplot(2,1,1); plot(xx,yy);
grid on;
subplot(2,1,2); plot(x,y);
grid on;