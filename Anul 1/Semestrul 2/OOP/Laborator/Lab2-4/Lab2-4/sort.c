#include "sort.h"

// Date intrare:- adresa unei liste de tip Lista
//				- o functie de comparare
//				- ordine = 0 daca crescator
//						 = -1 daca descrescator
// Post: lista sortata
void sort(Lista* l, FunctieComparare cmpF, int ordine) {
	int i, j;
	for (i = 0; i < size(l); i++) {
		for (j = i + 1; j < size(l); j++) {
			Oferta* p1 = get(l, i);
			Oferta* p2 = get(l, j);
			if (cmpF(p1, p2) > 0 && ordine == 0 || cmpF(p1, p2) < 0 && ordine == -1) {
				//interschimbam
				set(l, i, p2);
				set(l, j, p1);
			}
		}
	}
}