#include "IteratorMultime.h"
#include "Multime.h"


void IteratorMultime::deplasare() {
	//gaseste prima lista nevida incepand cu locatia poz din tabela
	while (poz < multime.m && multime.l[poz] == nullptr) //cat timp mai avem locatii in TD si locatia nu este vida
		poz++;
	if (poz < multime.m)
		curent = multime.l[poz];
}


IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	poz = 0;
	deplasare();
}


void IteratorMultime::prim() {
	//se determina prima lista nevida
	poz = 0;
	deplasare();
}


void IteratorMultime::urmator() {
	curent = curent->urm;
	if (curent == nullptr) {
		poz = poz + 1;
		deplasare();
	}
}


TElem IteratorMultime::element() const {
	return curent->e;
}

bool IteratorMultime::valid() const {
	return (poz < multime.m) && (curent != nullptr);
}