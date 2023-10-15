nodes = [1, 1.8, 2.2];
nodevals = exp(nodes);

t = 1 : 0.01 : 3;
res = Lagrange(nodes, nodevals, t);

plot(t, res, 'color', 'green');
hold on;

resexp = exp(t);
plot(t, resexp, 'color', 'yellow');
legend('Interpolare Lagrange', 'Functia aproximata')
hold off;