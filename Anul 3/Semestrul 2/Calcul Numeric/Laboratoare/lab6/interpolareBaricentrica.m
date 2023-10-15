function ff=interpolareBaricentrica(x, y, xx)
%call ff=barycentricInterpolation(x,y,xx,c)
%x - nodes
%y - function values
%xx - interpolation points
%ff - values of interpolation polynomial  
    n=length(x)-1;
    c=ones(1,n+1);
    for j=1:n+1
        c(j)=prod(x(j)-x([1:j-1,j+1:n+1]));
    end
    c=1./c;
    n=length(x)-1;
    numer = zeros(size(xx));
    denom = zeros(size(xx));
    exact = zeros(size(xx)); %test if xx=nodes
    for j=1:n+1
    xdiff = xx-x(j);
    temp = c(j)./xdiff;
    numer = numer+temp*y(j);
    denom = denom+temp;
    exact(xdiff==0) = j;
    end
    ff = numer ./ denom;
    jj = find(exact);
    ff(jj) = y(exact(jj));
end
