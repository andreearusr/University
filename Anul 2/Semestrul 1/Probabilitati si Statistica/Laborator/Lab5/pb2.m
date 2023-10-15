%2. distr exp 
% Timpul T necesar ca o imprimanta sa printeze un afis are distr exp
% cu val medie 12 secunde (adic?a parametrul este 1/12 )
% est. val medie si deviatia standard pentru T.

%rez acc cerinte folosind exprnd 

nr_sim=1000;
x1=rndexp(nr_sim,1/12);

x2=exprnd(12,1,nr_sim);

[mean(x1),mean(x2)]
[std(x1,1),std(x2,1)]
