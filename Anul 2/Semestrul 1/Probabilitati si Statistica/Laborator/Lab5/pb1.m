clf;grid on; hold on;
%1. 46% gr 0, 40% gr A, 10% gr B, 4% gr AB
% simulati observare gr sang a unei pers alese aleator 
%afisati frecv relativa de aparitie a fiecarei gr sang + histograma

%rez cerinta si cu randsample

nr_sim=1000;
x1=rndvardisc([1:4],[0.46 0.4 0.1 0.04],nr_sim);
x2=randsample([1:4],nr_sim,replacement=true,[0.46 0.4 0.1 0.04]);

frecv_rel1=histc(x1,1:4)/nr_sim;
bar(1:4,frecv_rel1,'hist','FaceColor','b'); 

frecv_rel2=histc(x2,1:4)/nr_sim;
bar(1:4,frecv_rel2,'FaceColor','y'); 

set(findobj('type','patch'),'facealpha',0.7);xlim([0 5]);
xticks(1:4);
