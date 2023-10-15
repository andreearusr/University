function contor = patrat_i(N=500)
  %N=numarul de puncte generate 
  clf;
  hold on;
  axis square;
  contor=0;
  rectangle('Position',[0 0 1 1]); % [0 0 1 1] colt stanga jos, colt dreapta sus
  for i=1:N 
    x=rand;
    y=rand;
    P=[x,y];
    if pdist([[0.5,0.5];P]) <= 0.5
      contor++;
      %plot(x,y,'om','MarkerSize',7,'MarkerFaceColor','m');
      plot(x,y,'om','MarkerFaceColor','m');
    endif
  endfor
  
  contor=contor/N;
endfunction