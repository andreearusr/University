adauga([], _, _, _, _, []).
adauga([H|T], Elem, IndexCurent, NextIndex, Pow, [H, Elem|Rez]) :-
    IndexCurent =:= NextIndex,
    IndexCurent1 is IndexCurent + 1,
    NextIndex1 is NextIndex + Pow,
    Pow1 is Pow * 2,
    adauga(T, Elem, IndexCurent1, NextIndex1, Pow1, Rez),
    !.
adauga([H|T], Elem, IndexCurent, NextIndex, Pow, [H|Rez]) :-
    IndexCurent1 is IndexCurent + 1,
    adauga(T, Elem, IndexCurent1, NextIndex, Pow, Rez).

adaugaWrap(L, Elem, Rez) :-
    adauga(L, Elem, 1, 1, 2, Rez).
