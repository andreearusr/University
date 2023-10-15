function result = pade_cos(value)
syms x;

g = @(x) cos(x);
r_cos = my_pade(g, 4, 5, x);
result = vpa(subs(r_cos, x, value));