adaugaSfarsit([], Element, [Element]) :- !.
adaugaSfarsit([H], Element, [H, Element]) :- !.
adaugaSfarsit([H|T], Element, [H|Rez]) :-
    adaugaSfarsit(T, Element, Rez).

faNumar([H], 1, H) :- !.
faNumar([H|T], Pow, Rez) :-
    faNumar(T, Pow1, Rez1),
    Pow is Pow1 * 10,
    Rez is H * Pow + Rez1.

faLista(N, [N]) :- N < 10, !.
faLista(N, Rezultat) :-
    N1 is mod(N, 10),
    N2 is div(N, 10),
    faLista(N2, Rez),
    adaugaSfarsit(Rez, N1, Rezultat).

f(L1, L2, Rez) :-
    faNumar(L1, Pow, Nr1),
    faNumar(L2, Pow, Nr2),
    Sum is Nr1 + Nr2,
    faLista(Sum, Rez).
