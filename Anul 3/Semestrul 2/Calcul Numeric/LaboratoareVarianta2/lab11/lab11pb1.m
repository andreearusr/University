n = 10;
a = 1;
b = 4;
[nodes_cheb_1, coeff_cheb_1] = Gauss_Cheb_1(n)
[nodes_cheb_2, coeff_cheb_2] = Gauss_Cheb_2(n)
[nodes_hermite, coeff_hermite] = Gauss_Hermite(n)
[nodes_jacobi, coeff_jacobi] = Gauss_Jacobi(n, a, b)
[nodes_laguerre, coeff_laguerre] = Gauss_Laguerre(n, a)
[nodes_legendre, coeff_legendre] = Gauss_Legendre(n)