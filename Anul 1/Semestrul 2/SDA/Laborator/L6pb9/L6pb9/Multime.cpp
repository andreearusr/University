#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>


Nod::Nod(TElem e, Nod* urm) {
	this->e = e;
	this->urm = urm;
}


int hashCode(TElem e) {
	//pentru moment numarul e intreg
	return abs(e);
}

int Multime::d(TElem e) const{
	//dispersia prin diviziune
	return hashCode(e) % m;
}

Multime::Multime() {
	m = MAX; //initializam m cu o valoare predefinita
	n = 0;

   //se initializeaza listele inlantuite ca fiind vide
	for (int i = 0; i < m; i++)
		l[i] = nullptr;
}


bool Multime::adauga(TElem elem) {

	int i = d(elem); //locatia de dispersie

	Nod* p = l[i];
	//verificam daca elem este deja in multime
	while (p != nullptr)
	{
		if (p->e == elem)
			return false;
		p = p->urm;
	}

	//se creeaza un nod
	Nod* nou = new Nod(elem, nullptr);

	//se adauga in capul listei inlantuite de la locatia i
	nou->urm = l[i];
	l[i] = nou;
	n++;
	return true;

}


bool Multime::sterge(TElem elem) {
	
	int i = d(elem); //locatia de dispersie
	Nod* p = l[i];

	if (p != nullptr) {
		if (p->e == elem) //verificam daca e elementul din capul listei
		{
			l[i] = l[i]->urm;
			delete p;
			n--;
			return true;
		}

		while (p->urm != nullptr)
		{
			if (p->urm->e == elem)
			{
				Nod* aux;
				aux = p->urm;
				p->urm = p->urm->urm;
				delete aux;
				n--;
				return true;
			}
			p = p->urm;
		}
	}

	return false;
}


bool Multime::cauta(TElem elem) const {

	int i = d(elem);  //locatia de dispersie

	Nod* p = l[i];
	while (p != nullptr)
	{
		if (p->e == elem)
			return true;
		p = p->urm;
	}

	return false;
}


int Multime::dim() const {
	return n;
}

bool Multime::vida() const {
	if(n==0)
		return true;
	return false;
}


Multime::~Multime() {
	//se elibereaza memoria alocata listelor
	for (int i = 0; i < m; i++) {
		//se elibereaza memoria pentru lista i
		while (l[i] != nullptr) {
			Nod* p = l[i];
			l[i] = l[i]->urm;
			delete p;
		}
	}
}


IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}


int Multime::diferenta(const Multime& b)
{
	int nr = 0;
	IteratorMultime im = b.iterator();
	
	for (int i = 0; i < b.dim(); i++)
	{
		int el = im.element();
		if (this->cauta(el)==true)
		{
			this->sterge(el);
			nr++;
		}
		im.urmator();
	}

	return nr;
}
