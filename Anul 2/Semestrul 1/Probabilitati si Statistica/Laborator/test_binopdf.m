binopdf(4,10,0.5)

N=1000;
count_4_din_10_albe=0;

for i=1:N
  nr_bile_albe_din_10_o_sim = binornd(10,0.5);
  if nr_bile_albe_din_10_o_sim==4
    count_4_din_10_albe++;
  endif
endfor  

prob_estimata = count_4_din_10_albe/N