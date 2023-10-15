function y=pb2()
%{
start = 10;
endd = 15;
cn = zeros(1, endd-start);

for k=10:15
    H = hilb(k);
    cn(k-start+1) = cond(H, 2); % numarul de conditionare
end

plot(start:endd, log10(cn),'r*')
%}

%{
for n=10:15
  printf('conditionare pt matricea Hilbert de n=%d este %f\n', n, cond(hilb(n), 2));
end
%}

fprintf("n cond_2  est.cond  teoretic\n")
for n=[10:15]
  H=hilb(n);
  et=(sqrt(2)+1)^(4*n+4)/(2^(14/4)*sqrt(pi*n)); %nr de cond relativ la norma euclid
  x=[n, norm(H)*norm(invhilb(n)), cond(H), et];
  fprintf("%d %g %g %g\n",x)
end


end
