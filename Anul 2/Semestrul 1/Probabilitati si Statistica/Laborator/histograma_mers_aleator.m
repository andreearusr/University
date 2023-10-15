clf;
grid on;hold on;
p=0.2; noduri=5;  nrpasi=10; nr_sim=1000;
axis([-nrpasi-1 nrpasi+1 0 0.5]);

nr_pasi_dreapta = zeros(1, nr_sim);

x=zeros(1, nr_sim); %pozitiile finale din simulari
for i=1:nr_sim
  [pozitii_vizitate, nr_p] = mers_aleator(nrpasi, p);
  nr_pasi_dreapta(i) = nr_p;
  x(i) = mod(pozitii_vizitate(end),noduri); %end -> te duce la ultimul elem
endfor

N=histc(x,0:noduri-1);

bar(0:noduri-1,N/nr_sim,'hist','FaceColor','b');
xticks(0:noduri-1);

fprintf('Poz. finale cele mai frecvente: %d.\n',find(N==max(N))-1);
fprintf('Valoarea medie de pasi la dreapta %d.\n', mean(nr_pasi_dreapta));