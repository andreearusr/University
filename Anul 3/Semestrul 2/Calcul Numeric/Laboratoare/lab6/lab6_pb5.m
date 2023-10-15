f = @exp;
nodes = [1 1.5 2];
nodeValues = f(nodes);
xi = 1.2;
aprox = interpolareBaricentrica(nodes, nodeValues, xi)
y = f(xi)