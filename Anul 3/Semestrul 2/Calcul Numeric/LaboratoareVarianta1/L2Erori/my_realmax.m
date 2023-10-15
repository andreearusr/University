% cel mai mare nr reprez in VF
function maxVF = my_realmax()
  maxAnt=2^10;
  maxx=2^10;

  while (maxAnt != Inf)
      maxx = maxAnt;
      maxAnt=maxAnt*2;
  end

  maxVF = (2-eps)*maxx;
end
