maxim([], MaximCurent, MaximCurent).
maxim([H|T], MaximCurent, MaximGlobal) :-
    H > MaximCurent,
    maxim(T, H, MaximGlobal),
    !.
maxim([_|T], MaximCurent, MaximGlobal) :-
    maxim(T, MaximCurent, MaximGlobal).

pozitii([], _, _, []).
pozitii([H|T], Maxim, Index, [Index|Rez1]) :-
    H =:= Maxim,
    Index1 is Index + 1,
    pozitii(T, Maxim, Index1, Rez1),
    !.
pozitii([_|T], Maxim, Index, Rez) :-
    Index1 is Index + 1,
    pozitii(T, Maxim, Index1, Rez).

f([H|T], Rez) :-
    maxim([H|T], H, Maxim),
    pozitii([H|T], Maxim, 1, Rez).
