#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
using namespace std;

bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Colectie::Colectie() {
	this->cp = MAX;
	this->el = new Telem[this->cp];
	this->st = new TElem[this->cp];
	this->dr = new TElem[this->cp];

	this->rad = -1;
	this->len = 0;

	dr[0] = -1;
	st[0] = -1;
	el[0].first = -1;
	el[0].second = 0;

	primLiber = new Node{ nullptr, 0 };
	Node* prim = primLiber;

	for (int i = 1; i <= this->cp; i++)
	{
		el[i].first = -1;
		el[i].second = 0;
		st[i] = -1;
		dr[i] = -1;

		primLiber->urm = new Node{ nullptr, i };
		primLiber = primLiber->urm;
	}
	primLiber = prim;

}

int Colectie::aloca(){
	int i = primLiber->i;
	primLiber = primLiber->urm;
	return i;
}

void Colectie::dealoca(int i)
{
	this->el[i] = { -1, 0 };
	st[i] = -1;
	dr[i] = -1;
}


void Colectie::adauga_recursiv(int r, TElem e, int parinte)
{
	if (r == -1) {
		r = aloca();
		if (rel(e, this->el[parinte].first)) {
			st[parinte] = r;
		}
		else {
			dr[parinte] = r;
		}
		this->el[r].first = e;
		this->el[r].second = 1;
		return;
	}
	else if (e == this->el[r].first) {
		this->el[r].second = this->el[r].second + 1;
		return;
	}

	if (rel(e, this->el[r].first))
		adauga_recursiv(st[r], e, r);
	else 
		adauga_recursiv(dr[r], e, r);
}


void Colectie::adauga(TElem e) {

	this->len++;
	if (rad == -1)
	{
		rad = aloca();
		this->el[rad].first = e;
		this->el[rad].second = 1;
		return;
	}
	adauga_recursiv(rad, e, -1);

}

int Colectie::sterge_recursiv(int r, TElem e)
{
	int nou;
	if (r == -1) {
		return -1;
	}
	else
	{
		if (rel(e, this->el[r].first))
		{
			st[r] = sterge_recursiv(st[r], e);
			return r;
		}
		else if (rel(this->el[r].first, e))
		{
			if (rel(this->el[r].first, e))
			{
			dr[r] = sterge_recursiv(dr[r], e);
			return r;
			}

		if (this->el[r].second == 0)
			return -1;
		if (this->el[r].second > 1) {
			this->el[r].second--;
			return r;
		}
		if (st[r] != -1 && dr[r] != -1) {
			int temp = minim(dr[r]);
			this->el[r] = this->el[temp];
			dr[r] = sterge_recursiv(dr[r], this->el[r].first);
		}
		else {
			int temp = r;
			int p;
			if (st[r] == -1) {
				p = dr[r];
			}
			else {
				p = st[r];
			}
			dealoca(temp);
			return p;
		}
		return r;
			
		}
	}
	return r;
}

bool Colectie::sterge(TElem e) {
	int r = cauta_recursiv(rad, e);
	if (r == -1) 
		return false;
	rad = sterge_recursiv(rad, e);
	if (this->len > 0)
		this->len--;
	if (r == -1)
		return false;
	return true;
}


int Colectie::minim(int p) {
	while (st[p] != -1)
	{
		p = st[p];
	}
	return p;
}

int Colectie::cauta_recursiv(int r, TElem e)
{
	if (r == -1 || e == this->el[r].first)
		return r;
	else
	{
		if (rel(e, this->el[r].first))
			return cauta_recursiv(st[r], e);
		else
			return cauta_recursiv(dr[r], e);
	}
}


bool Colectie::cauta(TElem elem) {
	int r = cauta_recursiv(rad, elem);
	if (r == -1)
		return false;
	return true;
}


int Colectie::nrAparitii(TElem elem) {
	int p = cauta_recursiv(rad, elem);
	if (p == -1) 
		return 0;
	else
		return this->el[p].second;
}


void Colectie::redim() {

	Telem* el_nou = new Telem[2 * this->cp];
	int* nou_st = new int[2 * this->cp];
	int* nou_dr = new int[2 * this->cp];
	int i;
	for (i = 1; i <= this->cp; i++)
	{
		el_nou[i] = this->el[i];
		nou_st[i] = this->st[i];
		nou_st[i] = this->dr[i];
	}
	for (int i = this->cp + 1; i <= 2 * this->cp; i++)
	{
		st[i] = 0;
		dr[i] = 0;
	}

	/*delete this->el;
	delete this->st;
	delete this->dr;*/

	el = el_nou;
	st = nou_st;
	dr = nou_dr;

	this->cp = 2 * this->cp;
}

int Colectie::dim() const {
	return this->len;
}


bool Colectie::vida() const {
	return this->len == 0;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/*delete[] this->el;
	delete[] this->st;
	delete[] this->dr;*/
}
