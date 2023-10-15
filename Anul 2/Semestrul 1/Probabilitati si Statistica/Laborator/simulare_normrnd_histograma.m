%x=normrnd(m,s,l,c)
%m=media
%s=sigma=deviatia standard
%l=nr linii
%c=nr coloane
nr_bare=20;
x=normrnd(165,10,1,10000);
%hist(x);
[~,mijloace]=hist(x,nr_bare);

NORM=nr_bare/(max(x)-min(x));
clf;
hold on;
hist(x, mijloace, NORM)

diviziune = linspace(min(x), max(x), 1000); % genereaza o div de 1000 val intre min si max, echidistante
valori = normpdf(diviziune, 165, 10);
plot(diviziune, valori, '-r', 'linewidth', 2)
axis([120,210,0,0.045])

mean(x)
std(x,1)

mean(x>160 & x<170)
normcdf(170,165,10)-normcdf(160,165,10)

