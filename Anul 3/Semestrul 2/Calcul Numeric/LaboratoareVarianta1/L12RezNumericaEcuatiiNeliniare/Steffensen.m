function [z,ni]=Steffensen(g,p0,ea,er,Nmax)
    %Steffensen - metoda Steffensen pentru ecuatii in R
    %intrare
    %g - functia f(x) = 0 => x = g(x)
    %p0 - valoarea de pornire
    %ea,er - eroarea absoluta, resp eroarea relativa
    %Nmax - numarul maxim de iteratii
    %iesire
    %z - aproximatia radacinii
    %ni - numar de iteratii

    if nargin<5, Nmax=50; end
    if nargin<4, er=0; end
    if nargin<3, ea=1e-3; end

    for k=1:Nmax
        p1 = g(p0);
        p2 = g(p1);
        p = p0 - ((p1-p0)^2/(p2-2*p1+p0));

        if abs(p-p0)<ea+er*p %succes
            z=p;
            ni=k;
            return
        end
        p0 = p;
    end
    %esec
    error('numarul maxim de iteratii depasit')
end
