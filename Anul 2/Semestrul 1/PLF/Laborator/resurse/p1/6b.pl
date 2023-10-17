maxim([], Nr, Rez):-!,
    Rez is Nr.
maxim([H|T], Nr, Rez) :- H > Nr,!,
    Nr1 is H,
    maxim(T, Nr1, Rez).
maxim([H|T], Nr, Rez) :- H =< Nr,
    Nr1 is Nr,
    maxim(T, Nr1, Rez).

max([H|T], Rez):-maxim([H|T], H, Rez).

% eliminareMax(L, C, Rez)

eliminareMax([], _, []) :- !.
eliminareMax([H|T], C, Rez):-max(C, M),
    M=H,!,
    eliminareMax(T, C, Rez).
eliminareMax([H|T], C, [H|Rez]):-max(C,M),
    M\=H,
    eliminareMax(T, C, Rez).

eliminareMaxim(L, Rez):-eliminareMax(L,L,Rez).
