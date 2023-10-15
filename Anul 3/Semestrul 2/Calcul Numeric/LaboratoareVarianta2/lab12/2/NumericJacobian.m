function J = NumericJacobian(f,x)
    n = length(x);
    fx=feval(f,x);
    step = 1e-6;

    for i=1:n
        xstep = x;
        xstep(i)=x(i)+step;
        J(:,i)=(feval(f,xstep)-fx)/step;
    end
end
