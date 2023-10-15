%2. X ~ Bino(n,p)
% a) sa se genereze un vector x de m valori ale lui X -> binornd
% comparati datele obt cu cele de distributie, fol: bar, binopdf, histc

clf;grid on; hold on;
n=5; p=1/3; nr_sim=5000;% nr_sim=m

% generate m values following the binomial law with n tries and probability p;
x=binornd(n,p,1,nr_sim);

% histogram of values from the binomial distribution;
N=hist(x,0:n);

% bar graph with the frequencies;
bar(0:n,N/nr_sim,'hist','FaceColor','b');  

% theoretical binomial distribution;
bar(0:n,binopdf(0:n,n,p),'FaceColor','y');

% legend for the figure;
legend('probabilitatile estimate','probabilitatile teroretice');

set(findobj('type','patch'),'facealpha',0.7);xlim([-1 n+1]);

% b) folosinf fct binornd in 5000 sim,  estimati prob ca 2 zaruri din 5
% sa arate nr divizibile cu 3.
% comp val. cu prob. teoretica coresp, folosind fct binopdf

prob_estim = sum( binornd(5, 1/3, 1, 5000) == 2)/5000
prob_teor = binopdf(2,5,1/3) %(x, n, p)
