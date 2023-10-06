#include "IteratorColectie.h"
#include "Colectie.h"
#include<iostream>


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {

    if (col.rad != -1)
    {
        inordine(col.rad);
        prim();
    }
  /*  for (auto el : elems)
    {
        std::cout << el.first << " ";
        std::cout << el.second << " \n";
    }*/
   
}

void IteratorColectie::inordine(int r){
    if (r != -1)
    {
        inordine(col.st[r]);
        elems.push_back(col.el[r]);
        inordine(col.dr[r]);
    }
}

TElem IteratorColectie::element() const {
    return elems[poz].first;
}

bool IteratorColectie::valid() const {
    return this->nr < col.len;
}
void IteratorColectie::urmator() {

    if (frecv < elems[poz].second -1)
    {
        this->frecv++;  
        return;
    }
    this->nr++;
    if (this->poz < elems.size()-1) {
        this->frecv = 0;
        this->poz++;
        this->curent = elems[poz].first;
    }
}

void IteratorColectie::prim() {

    this->nr = -1;
    this->poz = 0;
    this-> curent = elems[poz].first;
    frecv = 0;
}
