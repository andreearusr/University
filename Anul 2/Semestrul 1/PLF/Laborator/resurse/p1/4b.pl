substituie([], _, _, []) :- !.
substituie([H|T], Val, List, [List|Rez1]) :-
    H =:= Val,
    substituie(T, Val, List, Rez1).
substituie([H|T], Val, List, [H|Rez1]) :-
    substituie(T, Val, List, Rez1).
