suma([], [], 0, []).

suma([H|T], [], Tr, [Digit|Rez]) :-
    Digit is mod((H + Tr), 10),
    suma(T, [], 0, Rez).

suma([H1|T1], [H2|T2], Tr, [Digit|Rez]) :-
    Digit is mod((H1 + H2 + Tr), 10),
    Tr1 is div((H1 + H2 + Tr), 10),
    suma(T1, T2, Tr1, Rez).
