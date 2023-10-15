function [x, iteratii] = Newton_radacini_multiple(f, f_derivat, x0, m, epsilon, nr_max_iteratii)
    % f - functia pentru care se doreste determinarea radacinii
    % f_derivat - derivata functiei f
    % x0 - valoarea initiala pentru aproximarea radacinii
    % m - multiplicitatea radacinii
    % epsilon - precizia dorita pentru aproximarea radacinii
    % nr_max_iteratii - numarul maxim de iteratii

    % Initializare
    iteratii = 0;
    x = x0;

    % Aplicarea metodei lui Newton
    %cat timp nu depasim numarul maxim de iteratii si cat timp avem precizia dorita, calculeaza solutia
    while abs(f(x)) > epsilon && iteratii < nr_max_iteratii
        x = x - m * f(x) / f_derivat(x);
        iteratii = iteratii + 1;
    end

    if iteratii == nr_max_iteratii
        fprintf('Metoda lui Newton nu a convergat in numarul maxim de iteratii.\n');
    end

    % Verificarea conditiei de convergenta
    if abs(f(x)) > epsilon
        disp("Metoda nu a convergat catre o solutie.");
    end
end
