function [g_nodes,g_coeff] = Gauss_Ceb2(n)
%GAUSS_CEB1 - noduri si coeficienti Gauss-Cebisev #2

  beta=[pi/2,1/4*ones(1,n-1)];
  alpha=zeros(n,1);
  [g_nodes,g_coeff] = Gaussquad(alpha,beta);
end
