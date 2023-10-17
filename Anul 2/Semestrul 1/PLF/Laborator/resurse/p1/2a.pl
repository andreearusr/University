cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
    A1 is B,
    B1 is mod(A, B),
    cmmdc(A1, B1, Rez1),
    Rez is Rez1.

cmmmc(A, B, Rez) :-
    Part is A * B,
    cmmdc(A, B, Cmmdc),
    Rez is Part // Cmmdc.

f([], 1) :- !.
f([H|T], Rez) :-
    f(T, Rez1),
    cmmmc(H, Rez1, Rez2),
    Rez is Rez2.
