#include "Iterator.h"
#include "LO.h"

#include <iostream>
#include <exception>

using namespace std;
using std::exception;

LO::LO(Relatie r) {
	this->el = new TElement[2];
	this->urm = new TElement[2];
	this->prec = new TElement[2];
	this->cp = 2;
	this->rel = r;
	this->len = 0;
	this->primLiber = 0;
	this->urm[primLiber] = NULL_TELEMENT;
	this->inc = -1;
	this->sf = -1;
	
}

// returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
int LO::dim() const {
	return this->len;
}

// verifica daca LO e vida
bool LO::vida() const {
	return this->len == 0;
}

// prima pozitie din LO
Iterator LO::prim() const {
	Iterator it = Iterator(*this);
	it.curent = this->inc;
	return it;
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	if(!poz.valid())
		throw exception();
	return poz.element();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	if (!poz.valid())
		throw exception();

	if (poz.curent == inc)
	{
		TElement vechi = el[this->inc];
		int vechi_primLiber = this->primLiber;
		this->primLiber = this->inc;
		this->inc = this->urm[inc];
		this->urm[this->primLiber] = vechi_primLiber;

		this->len--;
		poz.curent = this->inc;
		return vechi;
	}

	if (poz.curent == sf)
	{
		TElement vechi = el[this->sf];
		this->sf = this->prec[sf];
		this->prec[sf] = NULL_TELEMENT;

		this->len--;
		poz.curent = this->sf;
		return vechi;
	}

	int p = this->inc;
	while ( (urm[p] != NULL_TELEMENT) && (urm[p] != poz.curent))
	{
		p = urm[p];
	}

	if (urm[p] == poz.curent)
		{
			TElement vechi_TElement = this->el[poz.curent];
			while (urm[p] != NULL_TELEMENT)
			{
				el[urm[p]] = el[urm[urm[p]]];
				p = urm[p];
			}

			urm[prec[p]] = NULL_TELEMENT;
			int vechi_primLiber = primLiber;
			primLiber = p;
			urm[primLiber] = vechi_primLiber;
			prec[primLiber] = NULL_TELEMENT;
			this->len--;
			return vechi_TElement;

		}

	
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const {

	Iterator it = Iterator(*this);
	it.curent = -1;
	if ((inc == NULL_TELEMENT))
	{
		return it;
	}
	
	int p = this->inc;
	while ((p != NULL_TELEMENT) &&( this->el[p] != e) && (!rel(e, this->el[p]))) {
		p = urm[p];
	}

	if ((p != NULL_TELEMENT) && (this->el[p] == e))
	{
		it.curent = p;
		return it;
	}

	return it;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	if (urm[this->primLiber]==NULL_TELEMENT)
	{
		redim();
	}
	if ((this->inc == -1) || (this->sf == -1))
	{
		this->inc = this->sf = this->primLiber;
		this->primLiber = this->urm[this->primLiber];
		this->el[this->inc] = e;
		this->urm[this->inc] = NULL_TELEMENT;
		this->prec[this->inc] = NULL_TELEMENT;
		this->len++;
		return;
	}

	else if ((this->inc != -1) && this->rel(e, this->el[this->inc]))
	{
		int inc_vechi = this->inc;
		this->inc = this->primLiber;
		this->primLiber = this->urm[this->primLiber];
		this->el[this->inc] = e;
		this->urm[this->inc] = inc_vechi;
		this->prec[inc_vechi] = this->inc;
		this->prec[this->inc] = NULL_TELEMENT;
		this->len++;
		return;
	}

	else if ((this->sf != -1) && this->rel(this->el[this->sf], e))
	{
		this->urm[this->sf] = this->primLiber;
		this->prec[primLiber] = this->sf;
		this->sf = primLiber;
		this->primLiber = this->urm[this->primLiber];
		this->el[this->sf] = e;
		this->urm[this->sf] = NULL_TELEMENT;
		this->len++;
		return;
	}


	else
		{
			int q = this->inc;
			while ((urm[q] != -1) && (!this->rel(e, this->el[urm[q]])) )
				q = urm[q];
			int nou = this->primLiber;
			this->primLiber = this->urm[this->primLiber];
			this->el[nou] = e;
			this->urm[nou] = this->urm[q];
			this->urm[q] = nou;
			this->prec[nou] = q;
			this->prec[this->urm[nou]] = nou;
			this->len++;
			return;

		}
	
}

void LO::redim()
{
	TElement* nou = new TElement[2 * this->cp];
	int* nou_urm = new int[2 * this->cp];
	int* nou_prec = new int[2 * this->cp];
	
	int i;
	for (i = 0; i < this->cp; i++)
	{
		nou[i] = this->el[i];
		nou_urm[i] = this->urm[i];
		nou_prec[i] = this->prec[i];
	}
	delete this->el;
	delete this->urm;
	delete this->prec;

	el = nou;
	urm = nou_urm;
	prec = nou_prec;
	urm[this->primLiber] = i;

	this->cp = 2 * this->cp;
	for ( ; i <this->cp - 1; i++)
		urm[i] = i + 1;
	urm[this->cp - 1] = NULL_TELEMENT;

}



//destructor
LO::~LO() {
	delete[] this->el;
	delete[] this->urm;
	delete[] this->prec;
}
