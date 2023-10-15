
f = @(x) x^2/2 + x + 1 - exp(x);
f_derivat = @(x) x + 1 - exp(x);
x0 = 1;
nr_max_iteratii = 200;
epsilon = 1e-6;
m = 1;

%1a
[x, iteratii] = Newton_radacini_multiple(f, f_derivat, x0, m, epsilon, nr_max_iteratii);
iteratii
fprintf('Radacina: %.6f\n', x);

% iteratii = 11

%1b
radacina = Newton_remediu(f, f_derivat, x0, epsilon, nr_max_iteratii)
fprintf('Radacina gasita: %.6f\n', radacina);

%1c
%Metoda lui Newton pentru radacini multiple este mai rapida atunci cand cunoastem multiplicitatea
%Cunoasterea multiplicitatii usureaza calculul radacinei, utilizand formula directa si ne duce la o convergenta mai rapida
%pentru a doua metoda, necunoscand multiplicitatea, ajungem la NaN
