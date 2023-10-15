function [A, b] = generareSistem2(n)
% genereaza al doilea sistem
% n - dimensiunea sistemului
% A - matricea sistemului
% b - matricea termenilor liberi
    diagPrinc = 5 * ones(n, 1);
    pseudoDiag1 = -1 * ones(n - 1, 1);
    pseudoDiag3 = -1 * ones(n - 3, 1);
    A = diag(diagPrinc) + diag(pseudoDiag1, 1) + diag(pseudoDiag1, -1) ...
        + diag(pseudoDiag3, 3) + diag(pseudoDiag3, -3);
    b = A * ones(n,1);
end