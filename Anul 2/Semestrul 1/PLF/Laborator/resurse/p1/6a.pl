apare([], _) :- false, !.
apare([H|_], Elem) :-
    H =:= Elem,
    !.
apare([_|T], Elem) :-
    apare(T, Elem).

multime([], []) :- !.
multime([H|T], Rez) :-
    apare(T, H),
    multime(T, Rez).
multime([H|T], [H|Rez1]) :-
    not(apare(T, H)),
    multime(T, Rez1).

numarAparitii([], _, 0) :- !.
numarAparitii([H|T], Val, Rez) :-
    H =:= Val,
    numarAparitii(T, Val, Rez1),
    Rez is Rez1 + 1,
    !.
numarAparitii([_|T], Val, Rez) :-
    numarAparitii(T, Val, Rez).

build(_, [], []).
build(L, [H|T], [H|Rez1]) :-
    numarAparitii(L, H, Cnt),
    Cnt =:= 1,
    build(L, T, Rez1), !.
build(L, [_|T], Rez) :-
    build(L, T, Rez).

f(L, Rez) :-
    multime(L, Multime),
    build(L, Multime, Rez).
