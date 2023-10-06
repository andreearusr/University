#include "IteratorColectie.h"
#include "Colectie.h"
#include<iostream>
#include <exception>
using std::exception;

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {

    if (col.rad != -1)
    {
        inordine(col.rad);
        prim();
    }
}

void IteratorColectie::inordine(int r) {
    if (r != -1)
    {
        inordine(col.st[r]);
        elems.push_back(col.el[r]);
        inordine(col.dr[r]);
    }
}

TElem IteratorColectie::element() const {
    if (!valid())
        throw exception();
    return elems[poz].first;
}

bool IteratorColectie::valid() const {
    return this->nr < col.len;
}
void IteratorColectie::urmator() {

    if (!valid())
        throw exception();
    if (frecv < elems[poz].second)
    {
        this->frecv++;
        return;
    }
    this->nr++;
    if (this->poz < elems.size()-1){
        this->frecv = 1;
        this->poz++;
        this->curent = elems[poz].first;
    }
}

void IteratorColectie::prim() {
    this->nr = -1;
    this->poz = 0;
    this->curent = elems[poz].first;
    frecv = 1;
}
