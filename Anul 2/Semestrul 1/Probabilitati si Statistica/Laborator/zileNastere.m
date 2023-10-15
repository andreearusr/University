function contor = zileNastere(nrPers, zile, repetitii)
  contor=0;
  for i = 1:repetitii
     if length(unique(randi(zile,1,nrPers))) < nrPers
      contor++;
     endif
  endfor
  
  contor = contor/repetitii;
endfunction