%functia eroare
syms x
expo=sym(1)/sym(2);

f=exp(-x^2)
n=7
ft(x)=taylor(f,x,0,'Order',n+1)
erf1(x) = (2/pi^expo)*int(ft(t),0,x)

f2=(2/pi^expo)*int(f,x)
erf2(x)=taylor(f2,x,0,'Order',n+1)
Rnf=subs(diff(f,x,n+1),x,xi)*x^(n+1)/factorial(n+1)

vpa(erf(1))
vpa(erf1(1))
vpa(erf2(1))