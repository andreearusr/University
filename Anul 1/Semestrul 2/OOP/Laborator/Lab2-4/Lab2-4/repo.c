#include "repo.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


Lista* createLista()
{
	Lista* rez = malloc(sizeof(Lista));
	rez->lg = 0;
	rez->cap = 2;
	rez->elems = malloc(rez->cap * sizeof(ElemType));
	return rez;
}

Lista* copyLista(Lista* l, CopyFunction copyF)
{
	Lista* copie = createLista();
	for (int i = 0; i < size(l); i++)
	{
		ElemType o = l->elems[i];
		add(copie, copyF(o));
	}
	return copie;
}

Lista* destroyUltim(Lista* l)
{

	ElemType o = l->elems[l->lg - 1];
	//destroyOferta(o);
	l->lg -= 1;
	return o;

}


void destroyListaOferte(Lista* l)
{
	destroyLista(l, destroyOferta);
}

void destroyLista(Lista* l,DestroyFunction destrF)
{
	for (int i = 0; i < size(l); i++)
	{
		//ElemType o = l->elems[i];
		//destroyOferta(&l->elems[i]);
		destrF(l->elems[i]);
	}
	free(l->elems);
	free(l);
}

ElemType get(Lista* l, int poz)
{
	return l->elems[poz];
}

ElemType set(Lista* l, int poz, ElemType elem_nou)
{
	ElemType rez = l->elems[poz];
	l->elems[poz] = elem_nou;
	return rez;
}

int size(Lista* l)
{
	return l->lg;
}

void ensureCapacity(Lista* l)
{
	if (l->lg < l->cap)
		return;	// Avem destula memorie
	// Alocam mai multa memorie
	int newCapacity = l->cap * 2;
	ElemType* newElems = malloc(newCapacity * sizeof(ElemType));
	// Copiem elementele din vectorul vechi in vectorul
	// nou, de dimensiune dubla
	for (int i = 0; i < l->lg; i++)
		newElems[i] = l->elems[i];
	// Dealocam vectorul vechi
	free(l->elems);
	l->elems = newElems;
	l->cap = newCapacity;
}

void add(Lista* l, ElemType el)
{
	ensureCapacity(l);
	l->elems[l->lg] = el;
	l->lg++;
}



void del(Lista* l, int poz)
{
	destroyOferta(l->elems[poz]);

	if (poz + 1== size(l))
	{
		l->lg -= 1;
		return;
	}
	int i;

	for (i = poz; i < size(l) - 1; i++)
	{
		Oferta* next = get(l, i + 1);
		set(l, i, next);
		//repo->elems[i] = repo->elems[i + 1];
	}
	l->lg -= 1;
}
