adaugareFibonacci([], _, _, _, _, _, []) :- !.
adaugareFibonacci([H|T], Elem, Index, Un, Doi, Trei, [H, Elem|Rez]) :-
    Index =:= Un,
    Index1 is Index + 1,
    Patru is Doi + Trei,
    adaugareFibonacci(T, Elem, Index1, Doi, Trei, Patru, Rez),
    !.
adaugareFibonacci([H|T], Elem, Index, Un, Doi, Trei, [H|Rez]) :-
    Index1 is Index + 1,
    adaugareFibonacci(T, Elem, Index1, Un, Doi, Trei, Rez).

