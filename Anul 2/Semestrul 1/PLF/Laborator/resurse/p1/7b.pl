perechi([], _, []).
perechi([H, T], _, [[H, T]]).
perechi([_, H2, H3|T], [], Rez) :-
    perechi([H2, H3|T], [H3|T], Rez).
perechi([H1|T1], [H2|T2], [[H1, H2]|Rez1]) :-
    perechi([H1|T1], T2, Rez1).

f([H|T], Rez) :- perechi([H|T], T, Rez).
