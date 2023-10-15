%Pade
syms x 

R11 = mypade(exp(x), 1, 1, x)
R22 = mypade(exp(x), 2, 2, x)

G22 = mypade(log(1+x), 2, 2, x)
G31 = mypade(log(1+x), 3, 1, x)