#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;
private:
    ///O(n)
	//constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);

    //contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	/* aici e reprezentarea specifica a iteratorului*/
	//TElem *curent;
    int curent;
    int parcurscurent = 0;
    int poz=0;

public:

        ///O(n)
		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		///O(n)
		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		///Θ(1)
		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		///Θ(1)
		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};
