function contor = patrat_i2(N=500)
  %N=numarul de puncte generate 
  clf;
  hold on;
  axis square;
  contor=0;
  rectangle('Position',[0 0 1 1]);
  
  A=[0,0];
  B=[0,1];
  C=[1,1];
  D=[1,0];
  O=[0.5,0.5];
  for i=1:N 
    x=rand;
    y=rand;
    P=[x,y];
    PA=pdist([P;A]);
    PB=pdist([P;B]);
    PC=pdist([P;C]);
    PD=pdist([P;D]);
    PO=pdist([P;O]);
    
    if PA>PO && PB>PO && PC>PO && PD>PO
      contor++;
      plot(x,y,'pm','MarkerSize',7,'MarkerFaceColor','m');
    endif
  endfor
  
  contor=contor/N;
endfunction