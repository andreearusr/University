#include "domain.h"

#include <string.h>
#include <stdlib.h>

Oferta* createOferta(char* tip, double suprafata, char* adresa, double pret)
{
	Oferta* rez = malloc(sizeof(Oferta));
	int nrC = strlen(tip) + 1;
	rez->tip = malloc(nrC * sizeof(char));
	strcpy_s(rez->tip, nrC, tip);

	rez->suprafata = suprafata;

	nrC = strlen(adresa) + 1;
	rez->adresa = malloc(nrC * sizeof(char));
	strcpy_s(rez->adresa, nrC, adresa);

	rez->pret = pret;
	return rez;
}

Oferta* copyOferta(Oferta* o)
{
	return createOferta(o->tip, o->suprafata, o->adresa, o->pret);
}

void destroyOferta(Oferta* o)
{
	free(o->tip);
	free(o->adresa);
	free(o);
}

char* get_adr(Oferta* o)
{
	return o->adresa;
}

char* get_tip(Oferta* o)
{
	return o->tip;
}

double get_suprafata(Oferta* o)
{
	return o->suprafata;
}

double get_pret(Oferta* o)
{
	return o->pret;
}