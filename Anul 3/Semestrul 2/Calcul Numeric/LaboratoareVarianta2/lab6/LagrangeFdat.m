function [val] = LagrangeFdat(x, f, m, nodes)
    mNodes = nodes(1 : m);
    val = Lagrange(mNodes, f(mNodes), x);
end
