#include "list.h"

Lista* createLista()
{
	Lista* rez;
	rez->lg = 0;
	rez->cap = 2;
	rez->lista = malloc(rez->cap * sizeof(void*));
	return rez;
}

void destroyLista(Lista* l)
{
	for (int i = 0; i < l->lg; i++)
		destroyOferta(&l->lista[i]);
	free(l->lista);
	free(l);
}

Lista* copyLista(Lista* l, CopyFunction CF)
{
	Lista* copie = createLista();
	for (int i = 0; i < l->lg; i++)
	{
		void* o = get(l, i);
		add(&copie, CF(o));
	}
	return copie;
}

void* get(Lista* l, int poz)
{
	return l->lista[poz];
}

void add(Lista* l, void* el)
{
	ensureCapacity(l);
	l->lista[l->lg] = el;
	l->lg++;
}



void ensureCapacity(Lista* l)
{
	if (l->lg < l->cap)
		return;	// Avem destula memorie
	// Alocam mai multa memorie
	int newCapacity = l->cap * 2;
	void** newElems = malloc(newCapacity * sizeof(void*));
	// Copiem elementele din vectorul vechi in vectorul
	// nou, de dimensiune dubla
	for (int i = 0; i < l->lg; i++)
		newElems[i] = l->lista[i];
	// Dealocam vectorul vechi
	free(l->lista);
	l->lista = newElems;
	l->cap = newCapacity;
}

void* set(Lista* l, int poz, void* elem_nou)
{
	void* rez = l->lista[poz];
	l->lista[poz] = elem_nou;
	return rez;
}

int size(Lista* l)
{
	return l->lg;
}

void deleteOf(Lista* l, int poz)
{
	for (int i = poz; i < l->lg - 1; i++)
	{
		l->lista[i] = l->lista[i + 1];
	}

	l->lg -= 1;

}