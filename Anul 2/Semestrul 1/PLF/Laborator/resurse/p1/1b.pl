f([], []) :- !.
f([H|T], [H|Rez]) :-
    mod(H, 2) =:= 1,
    f(T, Rez).
f([H|T], [H, 1|Rez]) :-
    mod(H, 2) =:= 0,
    f(T, Rez).
