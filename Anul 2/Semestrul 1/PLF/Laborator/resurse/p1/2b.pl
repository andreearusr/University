adaugare([], _, _, _, []) :- !.
adaugare([H|T], V, I, P, [H, V|Rez1]) :-
    I =:= P,
    I1 is I + 1,
    P1 is P * 2,
    adaugare(T, V, I1, P1, Rez1).
adaugare([H|T], V, I, P, [H|Rez1]) :-
    I =\= P,
    I1 is I + 1,
    adaugare(T, V, I1, P, Rez1).
