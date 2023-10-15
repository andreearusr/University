t=0:0.001:2*pi;
x=cos(t);y=sin(t);
plot(x,y,'r');
axis equal

%functia de gradul 3
x=-1:0.01:1;
y=x.^3;
hold on
plot(x,y,'k')

%se observa ca avem doua solutii.
%aplicam metoda lui Newton
F=@(x) [x(1)^2+x(2)^2-1; x(1)^3-x(2)]
Fd=@(x,y) [2*x(1) 2*x(2); 3*x(1)^2 -1]

%solutia din cadranul III
[z_newton3,ni_newton3]=Newton(F,Fd,[-0.5;-0.5],1e-6)
plot(z(1),z(2),'o')

%solutia din cadranul I
[z_newton1,ni_newton1]=Newton(F,Fd,[0.5;0.5],1e-6)
plot(z(1),z(2),'og')
[z_aprox,ni_aprox]=AproximariSuccesive(F,[0.8;0.5],1e-6,50)
plot(z(1),z(2),'ob')
