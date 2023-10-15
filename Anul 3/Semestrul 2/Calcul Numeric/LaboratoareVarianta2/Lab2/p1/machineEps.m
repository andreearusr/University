function machineEps = machineEps()
  machineEps = 1;
  while (1 + machineEps) ~= 1 
    machineEps = machineEps / 2;
  end
  machineEps = machineEps * 2;
end