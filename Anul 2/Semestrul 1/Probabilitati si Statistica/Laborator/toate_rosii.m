function prob_estim_AB=toate_rosii(N=5000)
  %AB: toate cele 3 bile extrase sunt rosii
  count_AB=0;
  for i=1:N
    extragere = randsample('rrrrraaavv',3,replacement=false);
    if extragere(1)=='r' && extragere(2)=='r' && extragere(3)=='r'
      count_AB++;
    endif
   % sau if ismember('r',extragere)

  endfor
  prob_estim_AB = count_AB/N;
endfunction