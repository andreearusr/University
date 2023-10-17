f(M, N, []) :-
    M > N, !.
f(M, N, [M|Rez]) :-
    M1 is M + 1,
    f(M1, N, Rez).
