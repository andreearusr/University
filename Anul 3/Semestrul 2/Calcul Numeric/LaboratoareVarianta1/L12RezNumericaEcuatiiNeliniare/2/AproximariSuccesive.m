function [z,ni] = AproximariSuccesive(f,x0,eps,nmax)
    xp=x0(:);
    lambda = NumericJacobian(f,x0);
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