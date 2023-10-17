lungime([], 0) :- !.
lungime([_|T], Rez) :-
    lungime(T, Rez1),
    Rez is Rez1 + 1.

listDesc([], [], []) :- !.
listDesc([H|T], [H|Rez1], A) :-
    mod(H, 2) =:= 0,
    listDesc(T, Rez1, A).
listDesc([H|T], A, [H|Rez1]) :-
    mod(H, 2) =:= 1,
    listDesc(T, A, Rez1).

f(L, [LP|[LI]], NrPare, NrImpare) :-
    listDesc(L, LP, LI),
    lungime(LP, NrP),
    NrPare is NrP,
    lungime(LI, NrI),
    NrImpare is NrI.
