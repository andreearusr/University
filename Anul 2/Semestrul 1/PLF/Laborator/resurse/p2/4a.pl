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
