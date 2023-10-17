adaugaSfarsit([], Element, [Element]) :- !.
adaugaSfarsit([H], Element, [H, Element]) :- !.
adaugaSfarsit([H|T], Element, [H|Rez]) :-
    adaugaSfarsit(T, Element, Rez).

invers([], []).
invers([H|T], Rez) :-
    invers(T, Rez1),
    adaugaSfarsit(Rez1, H, Rez).

adauga(L, [], L) :- !.
adauga(L, [H|T], Rez):-
    adauga([H|L], T, Rez).

f([], _, _, []).
f([H|T], Elem, NewList, Rez2) :-
    H =:= Elem,
    f(T, Elem, NewList, Rez1),
    adauga(Rez1, NewList, Rez2),
    !.
f([H|T], Elem, NewList, [H|Rez]) :-
    f(T, Elem, NewList, Rez).

main(L, Elem, NewList, Rez) :-
    invers(NewList, NewListInvers),
    f(L, Elem, NewListInvers, Rez).

