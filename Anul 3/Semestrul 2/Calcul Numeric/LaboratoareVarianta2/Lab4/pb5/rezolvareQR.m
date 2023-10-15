function x = rezolvareQR(A, b)
% rezolvarea sistemului pe baza descompunerii LUP
% A - matricea sistemului 
% b - vectorul termenilor liberi
% x - rezultatul sistemului
  [Q, R] = qr(A);
  x = R\Q.'*b;
end