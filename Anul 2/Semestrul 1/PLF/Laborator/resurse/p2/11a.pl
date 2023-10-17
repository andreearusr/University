prim(N, Div) :-
    N >= 2,
    Div > div(N, 2),
    !.

prim(N, Div) :-
    N >= 2,
    Rest is mod(N, Div),
    Rest =\= 0,
    Div1 is Div + 1,
    prim(N, Div1).

ePrim(N) :- prim(N, 2).

dublarePrime([], []).
dublarePrime([H|T], [H, H|Rez]) :-
    ePrim(H),
    dublarePrime(T, Rez),
    !.
dublarePrime([H|T], [H|Rez]) :-
    dublarePrime(T, Rez).

