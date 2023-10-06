#pragma once
#include "IteratorColectie.h"
#include <utility>
#define MAX 70000
//#include <bits/stdc++.h>

using namespace std;

typedef int TElem;
typedef int TComparabil;

typedef std::pair<TComparabil, TElem>Telem;
typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;


struct Node {
	Node* urm;
	TElem i;

};

class Colectie {

	friend class IteratorColectie;

private:
	
	Telem* el;
	TElem* st;
	TElem* dr;

	int cp;
	int len;
	int rad;
	Node* primLiber;

	//theta(1)
	int aloca();

	//theta(1)
	void dealoca(int i);

	//theta(cp)
	void redim();

	//O(h)
	void adauga_recursiv(int r, TElem e, int parinte);

	//O(h)
	int sterge_recursiv(int r, TElem e);

	//O(h)
	int cauta_recursiv(int r, TElem e);

	//O(h)
	int minim(int p);


public:
	//theta(cp)
	//constructorul implicit
	Colectie();

	//O(h)
	//adauga un element in colectie
	void adauga(TElem e);

	//O(h)
	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//O(h)
	//verifica daca un element se afla in colectie
	bool cauta(TElem elem);

	//O(h)
	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem);

	//theta(1)
	//intoarce numarul de elemente din colectie;
	int dim() const;

	//theta(1)
	//verifica daca colectia e vida;
	bool vida() const;

	//theta(1)
	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();


};

