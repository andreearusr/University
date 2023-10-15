
% 11.a
% Sa se scrie un predicat care sa testeze daca o lista formata din
% numere intregi are aspect de "vale" "(o multime se spune ca are aspect
% de "vale" daca elementele descresc pana la un moment dat, apoi cresc.
% De ex. 10 8 6 9 11 13).

% el=integer   list=el*
% vale(L:list, Up:integer, Low:integer)
% f(L:list)
%
% L - lista de numere indexata de la 0
% [H|[H1|T]-   H- capul listei, H1|T- coada listei
% Up - variabila ajutatoare
% Low - variabila ajutatoare

% (i,i,i) - modelul de flux
vale([_],Up,Low) :-
	vale(Up,Low).

vale([H|[H1|T]],Up,Low) :-
	H<H1,
        L=[H1|T],
	Low1 is Low+1,
	vale(L,Up,Low1).

vale([H|[H1|T]],Up,Low) :-
	H>H1,
	Low=<1,
	L=[H1|T],
	Up1 is Up+1,
	vale(L,Up1,Low).

% (i,i) - modelul de flux
vale(Up,Low) :-
	Up>1,
	Low>1,
	!.

% (i) - modelul de flux
f(L) :-	vale(L,1,1).


go1 :- f([12,10,9,4,5,6,7]),
       f([12,9,6,3,5,6,7,8]),
       f([54,43,20,33]),
       f([34,5,9]).

go2 :- f([1,1,1,1]).
go3 :- f([2,3]).
go4 :- f([]).
go5 :- f([22,13,4,56,2,6,8]).




