function pb3()
  %v = d/t
  %v' = acceleratie

  timp = [0, 3, 5, 8, 13];
  distanta = [0, 225, 383, 623, 993];
  viteza = [75, 77, 80, 74, 72];

  acc = [0, diff(viteza) ./ diff(timp)]

  disp("Pozitia automobilului la momentul t=10 - Hermite");
  valHermite = interpolareHermite(timp, distanta, viteza, 10);
  disp(valHermite);

  disp("Viteza automobilului la momentul t=10 - Hermite");
  v = interpolareHermite(timp, viteza, acc, 10);
  disp(v);

  %interp1(timp, distanta, 10,'pchip')
end
