adaugaSfarsit([], Element, [Element]) :- !.
adaugaSfarsit([H], Element, [H, Element]) :- !.
adaugaSfarsit([H|T], Element, [H|Rez]) :-
    adaugaSfarsit(T, Element, Rez).

minim([], MinCurent, Rez) :- Rez is MinCurent, !.
minim([H|T], MinCurent, Rez) :-
    H < MinCurent,
    minim(T, H, Rez), !.
minim([_|T], MinCurent, Rez) :-
    minim(T, MinCurent, Rez).

minimWrapper([H|T], Rez) :- minim([H|T], H, Rez).

eliminare([], Rez, _, _, Rez) :- !.
eliminare([H|T], Rez, Minim, Done, Final) :-
    Done =:= 0,
    H =:= Minim,
    eliminare(T, Rez, Minim, 1, Final),
    !.
eliminare([H|T], Rez, Minim, Done, Final) :-
    adaugaSfarsit(Rez, H, Temp),
    eliminare(T, Temp, Minim, Done, Final).

f([H|T], Final) :-
    minimWrapper([H|T], Minim),
    eliminare([H|T], [], Minim, 0, Final).
