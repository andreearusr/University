% cel mai mic nr normalizat reprez in VF
function minN = my_realmin()
  e = 0;

  while 2^e > 0.
    e = e - 1;
  end

  e = e+53; %53 = lungimea mantisei într-un format double
  minN = 2^e;
end
