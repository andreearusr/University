function [nodes, coeff] = Gauss_Legendre(n)
    beta=[2,(4-([1:n-1]).^(-2)).^(-1)]; 
    alpha=zeros(n,1);
    [nodes, coeff] = Gauss_quad(alpha,beta);
end