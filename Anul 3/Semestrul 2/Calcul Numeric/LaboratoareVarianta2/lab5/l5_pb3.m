n = 10;

[A, b] = generareSistem1(n);
err = 10^(-16);

sol_Jacobi_1 = rezolvareJacobi(A, b, err)
sol_Gauss_Seidel_1 = rezolvareGaussSeidel(A, b, err)
sol_SOR_1 = rezolvareSOR(A, b, determinareOmega(A), err)

[A, b] = generareSistem2(n);
err = 10^(-16);

sol_Jacobi_2 = rezolvareJacobi(A, b, err)
sol_Gauss_Seidel_2 = rezolvareGaussSeidel(A, b, err)
sol_SOR_2 = rezolvareSOR(A, b, determinareOmega(A), err)
