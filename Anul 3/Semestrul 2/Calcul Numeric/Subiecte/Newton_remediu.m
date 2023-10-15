function x = Newton_remediu(f, df, x0, tol, max_iter)
  % Initializam cele trei ultime valori ale lui x
  x_last = [x0, x0, x0];

  for i = 1:max_iter
    if abs(df(x_last(1))) < eps
      printf('Derivata este apropiata de zero. Metoda poate sa nu convearga.\n');
      return;
    end

    % Estimam multiplicitatea radacinii folosind formula de la curs
    m = round(log(abs(f(x_last(2)) / f(x_last(3)))) / log(abs((x_last(2) - x_last(1)) / (x_last(3) - x_last(1)))));

    % Aplicam formula lui Newton pentru radacini multiple cu multiplicitatea estimata
    x = x_last(1) - m * f(x_last(1)) / df(x_last(1));

    % Verificam daca am ajuns suficient de aproape de solutie
    if abs(f(x)) < tol
      return;
    end

    % Actualizam valorile lui x_last cu ultima valoare calculata
    x_last = [x, x_last(1), x_last(2)];
  end

  printf('Solutia nu a convers dandu-se numarul de iteratii si precizia\n');
end
