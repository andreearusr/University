x=0:0.01:1;
plot(x,x,'b',x,cos(x),'g');
hold on

f=@(x) cos(x)-x;
fd=@(x) -sin(x)-1;

%metoda lui Newton
[z_newton,ni_newton]=Newton(f,fd,0.5,1e-6)
plot(z,z,'o')

%metoda secantei
[z_secanta,ni_secanta]=Secanta(f,0.5,1,1e-6)
plot(z,z,'xk')

%metoda Steffensen
g=@(x) cos(x);
[z_steffensen,ni_steffensen]=Steffensen(g,0.5,1e-6)
plot(z,z,'-r')
