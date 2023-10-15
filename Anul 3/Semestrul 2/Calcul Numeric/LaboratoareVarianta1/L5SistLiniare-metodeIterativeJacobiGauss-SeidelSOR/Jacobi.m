function [x,ni]=Jacobi(A,b,x0,err,nitmax)

%call [x,ni]=Jacobi(A,b,x0,err,nitmax)

%A - matricea sistemului
%b - vectorul termenilor liberi
%x0 - vectorul de start
%err - toleranta (implicit e 1e-3)
%nitmax - numar maxim de iteratii (default 50)
%x - solutia
%ni -numarul de iteratii realizate efectiv

%verificarea parametrului
if nargin < 5, nitmax=50; end
if nargin < 4, err=1e-3; end
if nargin <3, x0=zeros(size(b)); end


[m,n]=size(A);
if (m~=n) | (n~=length(b))
  error('dimensiuni ilegale')
end

%calculeaza T si c (pregatirea iteratiilor)
M = diag(diag(A));
N = M - A;
T = inv(M) * N;
c = inv(M) * b;
alfa = norm(T,inf);
x=x0(:);

for i=1:nitmax
  x0 = x;
  x = T * x0 + c;
  if norm(x-x0,inf) < (1-alfa)/alfa*err
    ni=i;
    return
  end
end
error('prea multe iteratii')

