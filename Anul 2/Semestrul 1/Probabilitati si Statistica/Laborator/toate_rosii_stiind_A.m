function prob_estim_cond=toate_rosii_stiind_A(N=5000)
  %A: cel putin o bila extrasa este rosie din cele 3 extrase
  %AB: toate cele 3 sunt rosii
  %B\A: toate cele 3 sunt rosii stiind ca cel putin o bila extrasa este rosie
  count_A=0;
  count_AB=0;
  for i=1:N
    extragere = randsample('rrrrraaavv',3,replacement=false);
    if extragere(1)=='r' || extragere(2)=='r' || extragere(3)=='r'
      count_A++;
      if extragere(1)=='r' && extragere(2)=='r' && extragere(3)=='r'
       count_AB++;
      endif
    endif
   % sau if ismember('r',extragere)

  endfor
  prob_estim_cond = count_AB/count_A;
endfunction