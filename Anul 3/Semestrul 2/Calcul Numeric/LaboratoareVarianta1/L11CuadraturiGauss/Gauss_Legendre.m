function [g_nodes,g_coeff] = Gauss_Legendre(n)
%GAUSS-LEGENDRE - noduri si coeficienti Gauss-Legendre

  beta = [2,(4-([1:n-1]).^(-2)).^(-1)];
  alpha = zeros(n,1);
  [g_nodes, g_coeff] = Gaussquad(alpha,beta);
end
