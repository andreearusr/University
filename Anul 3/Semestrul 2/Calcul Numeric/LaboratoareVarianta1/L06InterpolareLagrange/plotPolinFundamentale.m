function ax = plotPolinFundamentale(noduri, grad)
  % plot polin fundam cand se dau nodurile si gradul
  m = length(noduri) - 1;
  valori = zeros(length(grad), m+1); %valori

  for ind=1:length(grad)
    valori(ind,:) = polinFundamentale(noduri, grad(ind));
  end

  % fiecare coloana -> polinom
  hold
  for i=1:columns(valori)
    plot(grad, valori(:,i));
  end
end
