%arctangenta
syms x

f(x)=atan(x)
n=6
fTaylor(x)=taylor(f,x,0,'Order',n+1)

vpa(pi/4)
vpa(f(1))
vpa(fTaylor(1))

n=1
while(abs(vpa(subs(taylor(f,x,0,'Order',n),x,1),6)-vpa(f(1),6))>1/100000)
  n=n+1000
endwhile
%n=51001

