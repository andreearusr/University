%taylor pt ln(1+x)

syms x m

f(x)=log(1+x)

n=8
fTaylor(x)=taylor(f,x,0,'Order',n+1)
vpa(log(2),7)
vpa(f(1),7)
vpa(fTaylor(1),7)

x = 1;
n = 1;
sum = 0;

while abs(log(1+x) - sum) > 1/100000
  sum = sum + (-1)^(n+1) * x^n / n;
  n = n + 1;
end
disp(n); %50001

syms x
g(x) = log((1+x)/(1-x))

n=8
gTaylor(x)=taylor(g,x,0,'Order',n+1)
vpa(log(2),7)
vpa(g(1/3),7)
vpa(gTaylor(1/3),7)

n=1
while(abs(vpa(subs(taylor(g,x,0,'Order',n),x,1/3),6)-vpa(g(1/3),6))>1/100000)
  n=n+1
endwhile
disp(n); %10

dezvT=taylor(g,x,0,'Order',10);
vpa(subs(dezvT,x,1/3),10)
vpa(log(2))

%{
dezvT=taylor(g,x,0,'Order',10);
vpa(subs(dezvT,x,1/3),10)
vpa(log(2))

y = 1/3;
n = 1;
sum = 0;

while abs(log(2) - sum) > 1/100000
  sum = sum + (-1)^(n+1) * y^(2*n-1) / (2*n-1);
  n = n + 1;
end

disp(n);



%n=1
%while(abs(vpa(subs(taylor(f,x,0,'Order',n),x,1),6)-vpa(f(1),6))>1/100000)
%  n=n+1000
%endwhile
%n=50001

dezvT=taylor(f,x,0,'Order',50001);
vpa(subs(dezvT,x,1),10)
vpa(log(2))


n=1
while(abs(vpa(subs(taylor(g,x,0,'Order',n),x,1/3),6)-vpa(g(1/3),6))>1/100000)
  n=n+1
endwhile
disp(n)

dezvT=taylor(g,x,0,'Order',10);
vpa(subs(dezvT,x,1/3),10)
vpa(log(2))
%}
