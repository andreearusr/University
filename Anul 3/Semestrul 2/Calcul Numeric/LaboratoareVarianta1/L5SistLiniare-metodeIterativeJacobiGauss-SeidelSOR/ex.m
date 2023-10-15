

n = 3;
err = 10^-6;

A = [10, 2, 3; 3, 12, 4; 5, 2, 15]
b = [1; 2; 3]

A\b

x_jacobi = Jacobi(A,b,err)
x_gauss_seidel = Gauss_Seidel(A,b,err)

omega = find_omega(A)
x_sor = SOR(A,b,omega,err)
