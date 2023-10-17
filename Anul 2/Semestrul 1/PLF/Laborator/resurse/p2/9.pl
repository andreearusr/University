% sterg(L, Rez) (i, o)
% L - lista din care se vor sterge secventele consecutive
% Rez - variabila colectoare

sterg([], []) :- !.
sterg([H1], [H1]) :- !.
sterg([H1, H2], []) :-
    H2 =:= H1 + 1, !.
sterg([H1, H2], [H1, H2]) :- !.
sterg([H1, H2, H3|T], Rez) :-
    H2 =:= H1 + 1,
    H3 =:= H2 + 1, !,
    sterg([H2, H3|T], Rez).
sterg([H1, H2, H3|T], Rez) :-
    H2 =:= H1 + 1, !,
    sterg([H3|T], Rez).
sterg([H1, H2, H3|T], [H1|Rez]) :-
    sterg([H2, H3|T], Rez).

% f(L, Rez) (i, o)
% L - lista din care se vor stergere secventele consecutive din subliste
% Rez - variabila colectoare

f([], []) :- !.
f([H1|T], [H1|Rez]) :-
    not(is_list(H1)),
    f(T, Rez).
f([H1|T], [Sublist|Rez]) :-
    is_list(H1),
    sterg(H1, Sublist),
    f(T, Rez).

% Cazuri de testare
% f([1, [2, 3, 5], 9, [1, 2, 4, 3, 4, 5, 7, 9], 11, [5, 8, 2], 7], Rez).
% Rez = [1, [5], 9, [4, 7, 9], 11, [5, 8, 2], 7].
% f([], Rez).
% Rez = [].
% f([1, 2, 3, 4, 5], Rez).
% Rez = [1, 2, 3, 4, 5].
