% sumaAlternanta(L:lista, I:integer, Suma:integer)
% L - lista pe care se face suma alternanta
% I - indicele curent in lista
% Suma - variabila colectoare

sumaAlternanta([], _, 0).
sumaAlternanta([H|T], I, Suma) :- mod(I, 2) =:= 0,
    I1 is I + 1,
    sumaAlternanta(T, I1, Suma1),
    Suma is Suma1 + H.
sumaAlternanta([H|T], I, Suma) :- mod(I, 2) =\= 0,
    I1 is I + 1,
    sumaAlternanta(T, I1, Suma1),
    Suma is Suma1 - H.
