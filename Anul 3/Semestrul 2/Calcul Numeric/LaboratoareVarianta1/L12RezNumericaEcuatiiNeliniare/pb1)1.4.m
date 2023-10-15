
x=0:0.01:1;

f=@(x) cos(x)-x^2;
fderivat=@(x) -sin(x) -2*x; %derivata

%metoda lui Newton
[z_newton,ni_newton]=Newton1(f,fderivat,0.5)

%metoda secantei
[z_secanta,ni_secanta]=secanta(f,0.5,1)

%metoda Steffensen
[z_steffensen,ni_steffensen]=Steffensen(f,0.5,1e-7)
