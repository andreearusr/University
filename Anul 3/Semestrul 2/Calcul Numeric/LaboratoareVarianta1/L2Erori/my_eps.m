% calcul epsilon-masina
%cel mai mic numar pozitiv care poate fi repr in virgula mobila
function eps = my_eps()
  eps=1;
  while (1+eps) > 1
      eps=eps/2;
  end
  eps=2*eps;
end

