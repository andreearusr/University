function machineRealmax = machineRealmax()
    max = 1;
    pwr2 = 1;
    while (2 * max ) ~= max 
        pwr2 = max;
        max = max * 2;
    end
    machineRealmax = pwr2 * (2 - eps);
end