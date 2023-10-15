function [A,b] = generareMatrici(n)
% genereaza sisteme de dimensiune n
% A - matrice de dimensiune n x n
% b - matrice coloana de dimensiune n

val = 30;
% generez random elementele matricei A cand timp matricea e singulara (det(A)=0)
while true
  A = ceil(unifrnd(-val, val ,n));
  if det(A) ~= 0; break; end
end

b = sum(A,2);
