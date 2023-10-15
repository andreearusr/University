%3.
%Un compan conectat la 2 imprimante: I1 si I2. Calc trimite printarea unui
% doc lui I1 cu prob 0,4, respectiv lui I2 cu prob 0,6.
% I1 printeaza un poster A2 in T1 secunde, unde T1 are distr Exp(1/5)
% iar I2 printeaza un poster A2 in T2 secunde, unde
%T2 are distributia uniforma Unif[4, 6].
% Un inginer solicita printarea unui poster A2 de pe computer.


N=1000;
r=rand(1,N);
y=exprnd(5,1,N).*(r<=0.4)+unifrnd(4,6,1,N).*(r>0.4);
mean(y)
std(y)
mean(y>5)
count1=0; count2=0;
for i=1:N
  r=rand;
  if r<=0.4
    I=1; 
    T=exprnd(5);
  else
    I=2;
    T=unifrnd(4,6);
  end
  if T>5
    count1++;
    if I==2
      count2++;
    endif
  endif
endfor
count2/count1
