function [z,ni] = Newton_ecuatiiScalare_sistem(f,fd,x0,ea,er,nmax)
%NEWTON - metoda lui Newton pentru ecuatii neliniare in R si Rˆn - ecuatii scalare si sisteme
%apel [z,ni]=Newton(f,fd,x0,ea,er,nmax)
%Intrare
%f - functia
%fd - derivata
%x0 - aproximatia initiala
%ea - eroarea absoluta (implicit 1e-3)
%er - eroarea relativa (implicit 0)
%nmax - numarul maxim de iteratii (implicit 50)

%Iesire
%z - aproximatia radacinii
%ni - numarul de iteratii

if nargin < 6, nmax=50; end
if nargin < 5, er=0; end
if nargin < 4, ea=1e-3; end

xp = x0(:); %x precedent

for k=1:nmax
  xc=xp-feval(fd,xp)\ feval(f,xp);

  if norm(xc-xp,inf)<ea+er*norm(xc,inf)
    z=xc; %succes
    ni=k;
    return
  end

  xp=xc;
end
error('S-a depasit numarul maxim de iteratii');

end
