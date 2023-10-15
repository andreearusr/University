
t=0:0.001:2*pi;
x=cos(t);
y=sin(t);

%functia de gradul 3
x=-1:0.01:1;
y=x.^3;

f=@(x) [x(1)^2+x(2)^2-1; x(1)^3-x(2)]
fd=@(x,y) [2*x(1) 2*x(2); 3*x(1)^2 -1]

%metoda lui Newton
[z_newton,ni_newton]=Newton_ecuatiiScalare_sisteme(f,fd,[0.5;0.5])

%metoda aproximatiilor succesive
[z_aprox,ni_aprox]=aprox_succesive(f,[0.8;0.5])

