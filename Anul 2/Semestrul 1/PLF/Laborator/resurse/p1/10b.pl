cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
    A1 is B,
    B1 is mod(A, B),
    cmmdc(A1, B1, Rez).

f([H], H) :- !.
f([H|T], Rez) :-
    f(T, Rez1),
    cmmdc(H, Rez1, Rez).
