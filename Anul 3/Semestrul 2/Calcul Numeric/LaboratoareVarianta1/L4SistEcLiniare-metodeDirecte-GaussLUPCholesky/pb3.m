% 3. Generati sisteme cu matrice aleatoare nesingulare ce
% au solutia [1,...,1]T. Rezolvati-le cu eliminare gaussiana
% si descompunere LUP.

[A,b] = generareMatrici(5);
A
b

x = Gausselim(A,b)

[L,U,P] = lup(A)
y2 = L\(P*b)
x2=U\y2

