%1. 
%a) simulati o astf. de depl. cu k paso, cu prob. p(0,1)
%returnati poz curente la fiecare pas

function [positions,steps2right]=mers_axa_a(p=0.5,k=10)
positions=zeros(1,k+1);
steps2right=0;
for j=2:k+1
   pas=2*binornd(1,p)-1 %(1-nr de incercari, p-probab.) - distr binomiala
   %pas=1 sau pas=-1
   positions(j)=positions(j-1)+pas;
   if pas==1
      steps2right++;
   end
 end