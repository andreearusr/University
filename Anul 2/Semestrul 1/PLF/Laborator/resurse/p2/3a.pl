merge(H, [], H) :- !.
merge([], H, H) :- !.
merge([H1|T1], [H2|T2], [H1|Rez]) :-
    H1 < H2,
    merge(T1, [H2|T2], Rez), !.
merge([H1|T1], [H2|T2], [H2|Rez]) :-
    H1 > H2,
    merge([H1|T1], T2, Rez), !.
merge([H1|T1], [H2|T2], [H1|Rez]) :-
    H1 =:= H2,
    merge(T1, T2, Rez).

split([], [], []) :- !.
split([A], [A], []) :- !.
split([H1, H2|T], [H1|Rez1], [H2|Rez2]) :-
    split(T, Rez1, Rez2).

mergeSort([], []) :- !.
mergeSort([H], [H]) :- !.
mergeSort(L, Rez) :-
    split(L, P1, P2),
    mergeSort(P1, Rez1),
    mergeSort(P2, Rez2),
    merge(Rez1, Rez2, Rez).
