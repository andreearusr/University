clf;
grid on;
hold on;
p=0.5;
n=10;
nr_sim=1000;
x=binornd(n,p,1,nr_sim);
N=histc(x,0:n);
bar(0:n,N/nr_sim,'hist','FaceColor','b');
bar(0:n,binopdf(0:n,n,p),'FaceColor','y');
legend('probabilitatile estimate','probabilitatile teroretice');
set(findobj('type','patch'),'facealpha',0.7);
xlim([-1 n+1]);

%xtics(0:n);