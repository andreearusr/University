#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1


class LO {
private:
	friend class Iterator;
	TElement* el;
	int cp;
	int len;
	int* urm;
	int* prec;
	int inc, sf, primLiber;
	Relatie rel;

	//O(n)
	void redim();

public:

	//Θ(1)
	// constructor
	LO(Relatie r);

	//Θ(1)
	// returnare dimensiune
	int dim() const;

	//Θ(1)
	// verifica daca LO e vida
	bool vida() const;

	//Θ(1)
	// prima pozitie din LO
	Iterator prim() const;

	//Θ(1)
	// returnare element de pe pozitia curenta
	//arunca exceptie daca poz nu e valid
	TElement element(Iterator poz) const;

	//O(n)
	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	void adauga(TElement e);

	//O(n)
	// sterge element de pe o pozitie poz si returneaza elementul sters
	//dupa stergere poz e pozitionat pe elementul de dupa cel sters
	//arunca exceptie daca poz nu e valid
	TElement sterge(Iterator& poz);

	//O(n)
	// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
	Iterator cauta(TElement e) const;


	//Θ(1)
	//destructor
	~LO();

};
