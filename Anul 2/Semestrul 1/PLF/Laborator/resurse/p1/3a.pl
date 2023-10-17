adaugaSfarsit([], E, [E]).
adaugaSfarsit([H|T], E, [H|Rez]) :-
    adaugaSfarsit(T, E, Rez).

apare([], _) :- false.
apare([H|_], E) :-
    E =:= H,
    !.
apare([_|T], E) :-
    apare(T, E).

multime([], M, M) :- !.
multime([H|T], M, Rez) :-
    not(apare(M, H)),
    !,
    adaugaSfarsit(M, H, R),
    multime(T, R, Rez).
multime([_|T], M, Rez) :-
    multime(T, M, Rez).
