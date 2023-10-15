% 2. Sa se implementeze descompunerea LUP. Sa se scrie rutine
% pentru rezolvarea unui sistem folosind descompunerea LUP.

A = [3,1,6;
    2,1,3;
    1,1,1;];
b = [3;4;8;];
[L,U,P] = lup(A)

y = L\(P*b)
x=U\y
A\b

%L UX = Pb
%L y = Pb => y = L\(P*b)
%UX = y => x = U\y


