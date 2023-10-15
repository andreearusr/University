
% 11.b
% Sa se calculeze suma alternanta a elementelor unei liste (l1 - l2+ l3 ...).
%
% el=integer   list=el*
% sumaAlt(L:list, Index:integer, Suma:integer)
% suma(L:list, S:integer)
%
% L - lista de numere indexata de la 0
% [H|T]- H- capul listei
% T- coada listei
% Index - indexul curent in lista
% Suma - variabila in care calculam suma alternanta
% S - variabila in care calculam suma alternanta

% (i,i,i) sau (i,i,o) - modelul de flux
sumaAlt([], _, 0).

sumaAlt([H|T], Index, Suma) :-  mod(Index, 2) =:= 0,
    Index1 is Index+1,
    sumaAlt(T, Index1, Suma1),
    Suma is Suma1 + H.


sumaAlt([H|T], Index, Suma) :- mod(Index, 2) =\= 0,
    Index1 is Index+1,
    sumaAlt(T, Index1, Suma1),
    Suma is Suma1 - H.


% (i,i) sau (i,o) - modelul de flux
suma(L,S):-sumaAlt(L,0,S).


go6 :- suma([1,2,3,4], -2),
       suma([], 0),
       suma([1,1,1,1], 0),
       suma([1,-1,1,-1], 4),
       suma([-2,-2,-2,-2], 0).
