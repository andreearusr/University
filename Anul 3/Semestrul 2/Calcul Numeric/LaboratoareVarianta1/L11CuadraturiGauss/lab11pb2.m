n = 100;
f = @(x)(sin(x.*x));
[nodes, coeff] = Gauss_Legendre(n);
GL = eval_integrala(nodes, coeff, f)
q = quad(f, -1, 1)
ql = quadl(f, -1, 1)