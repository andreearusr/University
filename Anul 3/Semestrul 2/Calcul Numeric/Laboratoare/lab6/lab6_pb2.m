nodes = [1 1.3 1.6 1.9];m = 4;labels = {};for k = 1 : m    t = 1 : 0.01 : 2;    p = evalPolinomFundamentalPuncteMultiple(nodes, k, t);    labels = [labels num2str(k)];    plot(t, p, 'color', rand(1,3))    hold on;endlegend(labels);hold off;