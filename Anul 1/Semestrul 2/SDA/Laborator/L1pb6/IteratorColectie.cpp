#include "IteratorColectie.h"
#include "Colectie.h"
#include <iostream>
using std::exception;



IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    prim();
}

void IteratorColectie::prim() {

    poz = 0;
    parcurscurent=0;
   //this->curent=0;

    bool gasit = false;
    for (this->curent = col.m; this->curent < col.M && !gasit; this->curent++)
        if (col.frecv[this->curent-col.m] !=0)
        {
            gasit = true;
            this->parcurscurent = 1;
            return;
        }

}

void IteratorColectie::urmator() {

    if (!valid())
        throw exception();
    poz++;
    bool gasit = false;
    if (parcurscurent < col.frecv[this->curent-col.m])
    {
        parcurscurent++;
        gasit = true;
        return;
    }

    for (this->curent = this->curent+1 ;this->curent < col.M && !gasit; this->curent++)
        if (col.frecv[this->curent-col.m] !=0)
        {
            parcurscurent = 1;
            gasit = true;
            return;
        }


}


bool IteratorColectie::valid() const {

    return poz < col.dim();
	//return curent-col.vect<col.dim();
}


TElem IteratorColectie::element() const {

	//elementul curent
    if (!valid())
        throw exception ();
    return this->curent;

}
