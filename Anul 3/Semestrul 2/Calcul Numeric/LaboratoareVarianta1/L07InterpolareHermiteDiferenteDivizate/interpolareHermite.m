function aprox = interpolareHermite(x, y, dy, xx)
  % returneaza valorile polinomului de interpolare Hermite
  % in punctele date

  herTable = tabelHermite(x, y, dy);
  q = herTable(1, 2:end);
  aprox = zeros(1, length(xx));

  for i = 1:length(aprox)
    coef = 1.;  % coeficientul actual
    for j = 1:length(q)
      aprox(i) = aprox(i) + coef * q(j);  % adauga la valoare polinomului
      x(ceil(j/2));
      coef = coef * (xx(i) - x(ceil(j/2)));
    end
end
