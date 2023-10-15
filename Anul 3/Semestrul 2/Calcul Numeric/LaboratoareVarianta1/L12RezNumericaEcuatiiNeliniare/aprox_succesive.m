function [z,ni] = aprox_succesive(f,x0,eps,nmax)

  if nargin<4, nmax=50; end
  if nargin<3, eps=1e-3; end

    xp=x0(:);
    lambda = numeric_jacobian(f,x0);
    for k=1:nmax
        xc = xp - lambda\feval(f,xp);
        if norm(xc-xp,inf)<eps
            z=xc; %succes
            ni=k;
            return
        end
        xp=xc;
    end
    error('S-a depasit numarul maxim de iteratii');
end
