function pbPract()

  %pb1
  vals = [1900 75.995
  1910 91.972
  1920 105.711
  1930 123.203
  1940 131.669
  1950 150.697
  1960 179.323
  1970 203.212
  1980 226.505
  1990 249.633
  2000 281.422
  2010 308.786];

  x = vals(:,1);
  y = vals(:,2);
  disp("Aproximarea populatiei din 1975 si 2018");
  disp(lagr(x, y, [1975 2018]));

  %pb2
  x = [1 1.1 1.2 1.3 1.4];
  y = fff(x);
  disp("Aproximarea functiei in 1.25");
  val = lagr(x, y, [1.25]);
  disp(val);

  disp("Delimitarea erorii");
  E = abs((fff(1.25) - val) / fff(1.25));
  disp(E);


  x = vals(:,1)
  y = vals(:, 2)
  c = barycentricweigths(x);
  xx = [1.25];
  disp("Interpolare baricentrica");
  ff = barycentricInterpolation(x, y, xx, c);
  disp(ff);

end
