function pb1()

  x=[0,1,2];
  f=exp(x);

  y = [exp(0), exp(1), exp(2)];
  dy = [exp(0), exp(1), exp(2)];
  xx = [0.25];

  disp("Valoare functiei in 0.25 - Hermite");
  valHermite = interpolareHermite(x,y,dy, 0.25);
  disp(valHermite);


  disp("Valoare functiei in 0.25 - Lagrange");
  valLagrange = lagr(x, y, [0.25]);
  disp(valLagrange);

  disp("Delimitarea erorii");
  E = abs(( f - valHermite) / f);
  disp(E);

  disp("Valoare functiei in 0.25 - soft");
  disp(interp1(x, y, [0.25],'pchip'));
end
