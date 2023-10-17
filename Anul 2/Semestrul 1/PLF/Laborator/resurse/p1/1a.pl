% apare([H|T], E). (i, i)
apare([], _) :-
    false.
apare([H|_], E) :-
    E = H,
    !.
apare([_|T], E) :-
    apare(T, E).

% diferenta(L1, L2, Rez). (i, i, o).
diferenta([], _, []) :- !.
diferenta([H|T], B, Rez) :-
    apare(B, H),
    diferenta(T, B, Rez),
    !.
diferenta([H|T], B, [H|Rez]) :-
    not(apare(B, H)),
    diferenta(T, B, Rez).
