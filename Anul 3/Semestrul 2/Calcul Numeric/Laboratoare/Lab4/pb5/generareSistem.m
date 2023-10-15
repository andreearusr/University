function [A,b] = generareSistem(n)
  triunghiInferior = tril(-1*ones(n),-1); 
  triunghiSuperior = zeros(n);
  triunghiSuperior(:,end)= ones(n,1);
  triunghiSuperior = triu(triunghiSuperior, 1);
  A = eye(n,n) + triunghiInferior + triunghiSuperior;
  b = [2:-1:-n+3]';
 end