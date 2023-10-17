elimina([], _, _, []) :- !.
elimina([H|T], Elem, Cnt, Rez) :-
    H =:= Elem,
    Cnt =\=0, !,
    Cnt1 is Cnt - 1,
    elimina(T, Elem, Cnt1, Rez).
elimina([H|T], Elem, Cnt, [H|Rez]) :-
    elimina(T, Elem, Cnt, Rez).
