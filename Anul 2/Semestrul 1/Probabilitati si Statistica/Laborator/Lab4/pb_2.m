%2. loto 6/49 pana nimereste un bilet cu cel putin 3 nr castig.
% i) gen. un vector x care cont. pt fiecare simulare nr de bilete necastig
% (care au cel mult 2 nr castig) pana la primul bilet castig
% (care are cel putin 3 nr castig)


%ii) "Cel putin 10 bilete succ sunt nnecastig pana cand juc nimereste
% un bilet castig”
%Comp probab estimata cu val teoretica folosind geopdf
m=1000;

%vect x care cont nr de bilete necastigatoare
p=sum(hygepdf(3:6,49,6,6)); %prob sa obtina 3,4,5,6, populatie de 49 bile, continand 6 bile marcate, alese random 6 nr fara returnare
x=geornd(p,1,m) %distr geometrica de parametru p, 1 rand, 1000 coloane => vector 1000 valori

prob_estim=mean(x>=10)
%geopdf - pt fiecare el de la 0:9, calc prob density func la X a distr geom cu param p
prob_teor=1-sum(geopdf(0:9,p)) 