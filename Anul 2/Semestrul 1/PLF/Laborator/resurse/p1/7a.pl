concatenare([], L, L).
concatenare([H|T], L, [H|Rez]) :-
    concatenare(T, L, Rez).

numarAparitii([], _, 0) :- !.
numarAparitii([H|T], Elem, Rez) :-
    H =:= Elem,
    numarAparitii(T, Elem, Rez1),
    Rez is Rez1 + 1, !.
numarAparitii([H|T], Elem, Rez) :-
    H =\= Elem,
    numarAparitii(T, Elem, Rez).

multime([], []).
multime([H|T], [H|Rez1]) :-
    numarAparitii([H|T], H, Cnt),
    Cnt =:= 1,
    multime(T, Rez1), !.
multime([H|T], Rez) :-
    numarAparitii([H|T], H, Cnt),
    Cnt =\= 1,
    multime(T, Rez).

f(L1, L2, Rez) :-
    concatenare(L1, L2, Rez1),
    multime(Rez1, Rez).
