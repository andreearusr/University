produs([], _, 0, []) :- !.
produs([], _, 1, [1]) :- !.

produs([H|T], Cif, Tr, [Digit|Rez]) :-
    Digit is mod((H * Cif + Tr), 10),
    Tr1 is div((H * Cif), 10),
    produs(T, Cif, Tr1, Rez).
