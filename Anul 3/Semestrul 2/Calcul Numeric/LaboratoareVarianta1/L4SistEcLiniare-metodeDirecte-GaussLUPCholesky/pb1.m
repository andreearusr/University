% 1. Implementati eliminarea gaussiana cu pivotare partiala sau
% scalata pe coloana (la alegere)

A = [10,7,3,1;
    3, 2, 6,8;
    5, 1, 5,3;
    1,1,1,1];
b = [7;
     4;
     6;
     1;];

x = Gausselim(A,b)
A\b
