function plotLagrange(f,noduri,puncteGrad)
  val = f(puncteGrad);
  valoriFunctie = f(noduri);
  valoriInterpolare = lagr(noduri, valoriFunctie, puncteGrad);

  hold;
  plot(puncteGrad, val);  % val lui f
  plot(puncteGrad, valoriInterpolare);  % valorile polinomului
end
