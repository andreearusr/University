% (i, i o)
apare([], _, Rez):-!,
    Rez is 0.
apare([H|_], Nr, Rez):-H=Nr,!,
    Rez is 1.
apare([H|T], Nr, Rez):-H\=Nr,
    apare(T, Nr, Rez).

lungime([], 0).
lungime([_|T], L):-
    lungime(T, L1),
    L is L1+1.

egale([], _, Rez):-!,
    Rez is 1.
egale([H|_], B, Rez):-apare(B, H, 0),!,
    Rez is 0.
egale([H|T], B, Rez):-apare(B, H, 1),
    egale(T, B, Rez).

multimiegale(A, B, Rez):-lungime(A, L1), lungime(B, L2), L1 \= L2,!,
    Rez is 0.
multimiegale(A, B, Rez):-lungime(A, L1), lungime(B, L2), L1 = L2,
    egale(A, B, Rez).
