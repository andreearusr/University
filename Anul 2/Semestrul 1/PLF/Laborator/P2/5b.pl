
% adaugaSf(L: list, E: el, R:list) - determinist
% model de flux: (i,i,o),(o,i, i),
%                (i,o,i),(i,i,i),(o,o,i)
% L - lista la care vrem sa adaugam un elementul E la sfarsit
% E - elementul de adaugat la sfarsitul listei L
% R - lista rezultat, obținută prin adăugarea elementului E la finalul
%     listei L
adaugaSf([],E,[E]).

adaugaSf([H|T], E, [H|R]):-
	adaugaSf(T,E,R).


% poz_lista(L:list, Rez:list, R:list) - determinist
% model de flux: (i,i,o),(i,i,i),(i,o,i)
% L- lista initiala
% Rez - lista rezultat initiala
% R - lista rezultat
poz_lista([], R, R).

poz_lista([H|T], Rez, R):-
	number(H),
	!,
	adaugaSf(Rez, H, Rez1),
	poz_lista(T, Rez1, R).

poz_lista([H|T], Rez, R):-
	is_list(H),
	!,
	f(H, Rr),
	adaugaSf(Rez, Rr, Rez1),
	poz_lista(T, Rez1, R).

%f(L:list, Rez:List) - determinist
%modele de flux: (i,o),(i,i)
% L- lista initiala
%Rez- lista rezultat
ff([H|T],Rez):-
	poz_lista([H|T], [], Rez).


t2 :-
	ff([1,[2,3],[4,1,4],3,6,[7,10,1,3,9],5,[1,1,1],7],[1,[2],[1,3],3,6,[2],5,[1,2,3],7]),
	ff([1,1,[4,5,5],6],[1,1,[2,3],6]),
	ff([[1,1],[0,0,0],[-5,-1,-3]],[[1,2],[1,2,3],[2]]).







