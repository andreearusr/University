lungime([_, _, _|_]) :- true.

count([_, _], 0) :- true, !.
count([H1, H2, H3|T], Rez) :-
    H1 < H2,
    H2 < H3,
    count([H2, H3|T], Rez),
    !.
count([H1, H2, H3|T], Rez) :-
    H1 > H2,
    H2 > H3,
    count([H2, H3|T], Rez),
    !.
count([H1, H2, H3|_], _) :-
    H1 < H2,
    H2 > H3,
    false,
    !.
count([H1, H2, H3|T], Rez) :-
    H1 > H2,
    H2 < H3,
    count([H2, H3|T], Rez1),
    Rez is Rez1 + 1.

f(L) :-
    lungime(L),
    count(L, Rez),
    Rez =:= 1.

