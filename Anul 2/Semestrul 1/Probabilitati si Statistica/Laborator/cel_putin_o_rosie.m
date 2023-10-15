function prob_estim_A=cel_putin_o_rosie(N=5000)
  %A: cel putin o bila extrasa este rosie din cele 3 extrase
  count_A=0;
  for i=1:N
    extragere = randsample('rrrrraaavv',3,replacement=false);
    if extragere(1)=='r' || extragere(2)=='r' || extragere(3)=='r'
      count_A++;
    endif
   % sau if ismember('r',extragere)

  endfor
  prob_estim_A = count_A/N;
endfunction