%aproximare MacLaurin

syms x

f=exp(x)
T2f=taylor(f,x,0,'Order',3)
T3f=taylor(f,x,0,'Order',4)
T4f=taylor(f,x,0,'Order',5)
T5f=taylor(f,x,0,'Order',6)

f=@(x)exp(x)
T2f=@(x)T2f

xx = linspace(-2, 2, 1000);
T2f(xx)
plot(x, f, 'b', x, T2f, 'r--', x, T3f, 'g--', x, T4f, 'm--', x, T5f, 'y--');
xlabel('x');
ylabel('y');
title('Taylor series approximations of e^x');
legend('e^x', '2nd order', '3rd order', '4th order', '5th order');

g=log(1+x)
G2f=taylor(g,x,0,'Order',3)
G3f=taylor(g,x,0,'Order',4)
G4f=taylor(g,x,0,'Order',5)
G5f=taylor(g,x,0,'Order',6)
