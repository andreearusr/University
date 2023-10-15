function result = pade_sin(value)
syms x;

f = @(x) sin(x);
r_sin = my_pade(f, 5, 4, x);
result = vpa(subs(r_sin, x, value));