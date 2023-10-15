function Q = adquad(f,a,b,tol)
%ADQUAD Cuadratura adaptiva
%apel [Q,fcount] = adquad(F,a,b,tol)
% F - functia
% a,b - intervalul
% tol precizia, implicit 1.e-6.

if nargin < 4 | isempty(tol), tol = 1.e-6; end

c = (a + b)/2;
fa = f(a); fc = f(c); fb = f(b);
Q = quadstep(f, a, b, tol, fa, fc, fb);

end
