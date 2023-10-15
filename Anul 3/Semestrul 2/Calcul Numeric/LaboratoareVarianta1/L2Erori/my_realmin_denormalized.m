% cel mai mic nr nenormalizat reprez in VF
% numar intre 0 si realmin sau 0 si cel mai mic nr normalizat
function minDN = my_realmin_denormalized()
  e = 0;
  realMin=my_realmin();

  while 2^e >= realMin
    e = e - 1;
  end

  minDN = 2^e;
end
