concatenare([], [], []) :- !.
concatenare([H|T], L, [H|Rez]) :-
    concatenare(T, L, Rez),
    !.
concatenare([], [H|T], [H|Rez]) :-
    concatenare([], T, Rez).

divizori(N, Div, []) :-
    Div > div(N, 2),
    !.
divizori(N, Div, [Div|Rez]) :-
    mod(N, Div) =:= 0,
    Div1 is Div + 1,
    divizori(N, Div1, Rez),
    !.
divizori(N, Div, Rez) :-
    Div1 is Div + 1,
    divizori(N, Div1, Rez).

main([], []).
main([H|T], [H|Rez]) :-
    divizori(H, 2, Div),
    main(T, Rez1),
    concatenare(Div, Rez1, Rez).
