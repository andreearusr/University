function I = eval_integrala(nodes, coeff, f)
    m = length(coeff);
    sum = 0;
    for k = 1:m
       sum = sum + coeff(k) * f(nodes(k)); 
    end
    I = sum;
end
