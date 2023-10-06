#pragma once
class Multime;
class Nod;
typedef int TElem;

class IteratorMultime
{
	friend class Multime;
	friend class Nod;
private:

	//O(m)
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//O(m)
	void deplasare();

	//contine o referinta catre containerul pe care il itereaza
	const Multime& multime;
	
	int poz;
	Nod* curent;

	

public:

	//O(m)
	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//O(m)
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
