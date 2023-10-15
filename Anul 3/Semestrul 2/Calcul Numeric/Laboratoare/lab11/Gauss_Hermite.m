function [nodes,coeff] = Gauss_Hermite(n)
    beta = [sqrt(pi),[1:n-1]/2];
    alpha = zeros(n,1);
    [nodes, coeff] = Gauss_quad(alpha,beta);
end