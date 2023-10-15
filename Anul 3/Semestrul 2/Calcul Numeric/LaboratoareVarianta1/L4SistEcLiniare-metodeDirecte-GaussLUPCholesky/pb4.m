% 4. Sa se scrie rutine pentru descompunerea Cholesky a unei
% matrice hermitiene si pozitiv definite si rezolvarea unui
% sistem cu o astfel de matrice prin descompunere Cholesky.
% Testati rutinele pentru matrice generate aleator si sisteme
% cu matrice aleatoare, dar cu solutie cunoscuta.

A = [1,1,1,1;
    1,2,3,4;
    1,3,6,10;
    1,4,10,20;];
b = [4;10;7;8];

R = Cholesky(A)
y = (R.')\b     % R.' - transpusa lui R
x = R\y


A1_conj = [];
A_transpus = [];
sylvester = false

while(A1_conj != A_transpus && sylvester == false)
  [A1,b1] = generareMatrici(5);
  A1_conj = conj(A1);
  A_transpus = transpose(A);
  sylvester = sylv(A1);
end


R1 = Cholesky(A1)
y1 = (R1.')\b1
x1 = R1\y1

%hermitiana + poz definita
%A=conjugat de A transpus
%+ criteriul lui Sylvester
