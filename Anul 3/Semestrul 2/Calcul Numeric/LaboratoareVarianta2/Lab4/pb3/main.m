[A, b] = generareSistem(4);
disp(A)
x_gauss = elimGaus(A,b);
x_lup = rezolvareLUP(A,b);
disp(x_gauss)
disp(x_lup)