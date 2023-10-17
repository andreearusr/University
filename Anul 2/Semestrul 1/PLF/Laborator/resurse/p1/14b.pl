f([H|_], 1, H).
f([_|T], N, Rez) :- N1 is N-1,
    f(T, N1, Rez).
