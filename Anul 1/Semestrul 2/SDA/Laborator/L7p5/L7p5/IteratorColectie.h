#pragma once
#include "Colectie.h"
#include <vector>
using std::vector;

class Colectie;
typedef int TElem;
typedef int TComparabil;
typedef std::pair<TComparabil, TElem>Telem;

class IteratorColectie
{
	friend class Colectie;

private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);

	//contine o referinta catre containerul pe care il itereaza
	const Colectie& col;

	vector<Telem> elems;
	int poz;
	int curent;
	int frecv;
	int nr;

	//Θ(h*h)
	void inordine(int r);


public:
	//Θ(1)
	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//Θ(1)
	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//Θ(1)
	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//Θ(1)
	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;
};

