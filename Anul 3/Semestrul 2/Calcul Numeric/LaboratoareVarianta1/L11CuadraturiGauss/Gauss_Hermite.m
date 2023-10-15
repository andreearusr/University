function [g_nodes,g_coeff] = Gauss_Hermite(n)
%GAUSS_HERMITE - noduri si coeficienti Gauss-Hermite

  beta = [sqrt(pi),[1:n-1]/2];
  alpha = zeros(n,1);
  [g_nodes, g_coeff] = Gaussquad(alpha,beta);
end
