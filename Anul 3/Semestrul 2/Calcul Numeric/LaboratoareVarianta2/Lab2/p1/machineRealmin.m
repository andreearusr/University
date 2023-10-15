function machineRealmin = machineRealmin()
    nr = 1;
    eps0 = 1;
    while nr ~= 0
        eps0 = nr;
        nr = nr / 2;
    end
    nr = eps0;
    minimum = nr;
    while (nr + minimum) ~= minimum
        minimum = minimum * 2;
    end
    machineRealmin = minimum / 2;
end