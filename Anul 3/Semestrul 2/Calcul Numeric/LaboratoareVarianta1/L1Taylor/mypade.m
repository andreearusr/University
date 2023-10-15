function R = mypade(f,m,k,x)
  
syms C a R bt vp

c=sym(zeros(m+k+1,1));
if m>k
    b=sym(zeros(m+1,1));
else
    b=sym(zeros(k+1,1));
end
a=sym(zeros(1,m+1));
%% 
% Compute Taylor coefficients
for p=0:m+k
    c(p+1)=subs(diff(f,x,p),x,0)/factorial(p);
end

% Build Toeplitz matrix and solve the system 
j=0:k-1;
C=toeplitz(c(m+j+1),c(m-j+1));
bv=-c(m+(1:k)+1);
b(2:k+1)=C\bv;
b(1)=1;
 
% Compute $a_j
syms j
for j=0:m
    a(j+1)=sym('0');
    for l=0:j
        a(j+1)=a(j+1)+c(j-l+1)*b(l+1); 
    end
end
vp=sum(a.*x.^(0:m));
vq=sum(b(1:k+1)'.*x.^(0:k));
R=vp/vq;
end