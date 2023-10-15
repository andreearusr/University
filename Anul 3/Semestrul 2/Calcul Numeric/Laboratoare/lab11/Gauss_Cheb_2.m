function [nodes, coeff] = Gauss_Cheb_2(n)
    beta=[pi/2,1/4*ones(1,n-1)];
    alpha=zeros(n,1);
    [nodes,coeff] = Gauss_quad(alpha,beta);
end