function [A,b] = matrice_diagonal_dominanta(n)
  max_element = 50;
  A = randi([-max_element,max_element],n);
  out = sum(abs(A),2) + randi(max_element, n,1); %suma el lui A pe fiecare rand => vector coloana
  for i=1:n
    A(i,i) = out(i);
  end
  b = A*([1:n]'); % b - vectorul termenilor liberi
end
