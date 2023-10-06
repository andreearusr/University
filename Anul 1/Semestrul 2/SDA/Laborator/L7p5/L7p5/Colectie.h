#pragma once
#include "IteratorColectie.h"
#include <utility>
#define MAX 70000

using namespace std;

typedef int TElem;
typedef int TComparabil;

typedef std::pair<TComparabil, TElem>Telem;
typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;


struct Nod {
	Nod* urm;
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
	Nod* primLiber;

	////Θ(cp)
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
	//Θ(cp)
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

	//Θ(1)
	//intoarce numarul de elemente din colectie;
	int dim() const;

	//Θ(1)
	//verifica daca colectia e vida;
	bool vida() const;

	//Θ(1)
	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

	int stergeToateElementeleRepetitive();
	/*
	Complexitati:
	-caz favorabil= caz mediu = caz defavorabil = Θ(len+size(v)*nr_ap)
	-caz general: Θ(len+size(v)*nr_ap)


	* pre: c este o Colectie
	* post: c'=c din care s-au eliminat ..
	* nr- numarul de elemente eliminate
	* returneaza numarul de elemente eliminate
	Subalgoritm stergeToareElemenreleRepetitive(c)
		nr <- 0
		vector<TElem> v;

		iterator(c,ic)
		CatTimp valid(ic) executa
			v<-element(ic)
			urmator(ic)
		SfCatTimp

		Pentru i=0,size(v) executa
			el<-v[i]
			nr_ap<-nrAparitii(v[i])
			Daca nr_ap>1 atunci
				Pentru i=0,nr_ap executa
					sterge(el)
				SfPentru
				nr<-nr+1
			SfDaca
		SfPentru
		
		@returneaza nr

	SfSubalgoritm

	 */

};

