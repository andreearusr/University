function pb2()

  x= [0.3, 0.32, 0.35];
  f=sin(x);

  y = [0.29552 , 0.31457, 0.34290];
  dy = [0.9553, 0.94924, 0.93937];
  xx = [0.34];

  disp("Valoare functiei in 0.34 - Hermite");
  valHermite = interpolareHermite(x,y,dy, 0.34);
  disp(valHermite);

  disp("Delimitarea erorii");
  E = abs((f - valHermite) / f);
  disp(E);

  disp("Valoare functiei in 0.34 - soft");
  disp(interp1(x,y, [0.34],'pchip'));


  %--------------------------------
  x2= [0.3, 0.32, 0.33, 0.35];
  f2=sin(x2);

  y2 = [0.29552 , 0.31457, sin(0.33), 0.34290];
  dy2 = [0.9553, 0.94924, cos(0.33) ,0.93937];

  disp("Valoare functiei in 0.33 - Hermite");
  valHermite2 = interpolareHermite(x2,y2,dy2, 0.34);
  disp(valHermite2);

  disp("Delimitarea erorii");
  E2 = abs((f2 - valHermite2) / f2);
  disp(E2);

  disp("Valoare functiei in 0.33 - soft");
  disp(interp1(x2, y2, [0.34],'pchip'));

end
