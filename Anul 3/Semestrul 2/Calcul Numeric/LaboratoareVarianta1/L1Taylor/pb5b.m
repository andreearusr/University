
syms x

g(x) = log((1+x)/(1-x))

n=8
gTaylor(x)=taylor(g,x,0,'Order',n+1)
vpa(log(2),7)

vpa(g(1/3),7)
vpa(gTaylor(1/3),7)

x = 1/3;
n = 1;
sum = 0;

while abs(log(2) - sum) > 1/100000
  sum = sum + (-1)^(n+1) * x^(2*n-1) / (2*n-1);
  n = n + 1;
end

disp(n);

