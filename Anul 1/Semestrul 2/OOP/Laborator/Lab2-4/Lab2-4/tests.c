#include <assert.h>
#include <string.h>
#include "domain.h"
#include "service.h"
#include "valid.h"


void test_creare_si_validare()
{
	assert(validare_criteriu("Tip") == 1);
	assert(validare_criteriu("ceva dar nu tip") == 0);

	Oferta* oferta = createOferta("casa", 425.43, "Cluj-Napoca nr.2", 643457.99);
	assert(strcmp(oferta->tip, "casa") == 0);
	assert(strcmp(oferta->adresa, "Cluj-Napoca nr.2") == 0);
	assert(oferta->pret == 643457.99);
	assert(oferta->suprafata == 425.43);

	Informatii info;
	info = validare(oferta);

	// Daca totul este ok
	assert(info.cod == 0);
	assert(strcmp(info.text, "Comanda realizata cu succes !\n") == 0);
	destroyOferta(oferta);

	// Cand un camp este gresit, ex: adresa este vida
	oferta = createOferta("casa", 425.43, "", 643457.99);
	info = validare(oferta);
	assert(info.cod == 1);
	assert(strcmp(info.text, "Adresa invalida !\n") == 0);
	destroyOferta(oferta);

	// Cand toate campurile sunt gresite
	oferta = createOferta("masina", -25, ")(*&^%$#@!", 0);

	info = validare(oferta);
	assert(info.cod == 1);
	assert(strcmp(info.text, "Tip invalid !\nSuprafata invalida !\nAdresa invalida !\nPret invalid !\n") == 0);
	destroyOferta(oferta);
}

void test_adaugare()
{
	Agentie* ag = creeazaAgentie();
	Informatii info;

	// Adaugare cu elemente valide
	info = SRV_adauga(ag, "casa", 425.43, "Cluj-Napoca nr.2", 643457.99);
	assert(info.cod == 0);
	assert(size(ag->Oferte) == 1);
	assert(strcmp(get_tip(ag->Oferte->elems[0]), "casa") == 0);
	assert(get_suprafata(ag->Oferte->elems[0]) == 425.43);
	assert(strcmp(get_adr(ag->Oferte->elems[0]), "Cluj-Napoca nr.2") == 0);
	assert(get_pret(ag->Oferte->elems[0]) == 643457.99);

	// Incercare de adaugare cu aceeasi adresa
	info = SRV_adauga(ag, "casa", 425.43, "Cluj-Napoca nr.2", 643457.99);
	assert(info.cod == 2);
	assert(strcmp(info.text, "Oferta deja existenta la aceasta adresa !\n") == 0);
	assert(size(ag->Oferte) == 1);
	
	//Adaugare cu elemente invalide
	info = SRV_adauga(ag, "masina", -65, "$%&$*", 0);
	assert(size(ag->Oferte) == 1);
	assert(info.cod == 1);
	assert(strcmp(info.text, "Tip invalid !\nSuprafata invalida !\nAdresa invalida !\nPret invalid !\n") == 0);
	
	undo(ag);
	assert(size(ag->undoList) == 0);
	destroyAgentie(ag);
}



void test_modificare()
{
	Agentie* ag = creeazaAgentie();
	Informatii info;
	SRV_adauga(ag, "casa", 425.43, "Cluj-Napoca nr.2", 643457.99);
	assert(size(ag->Oferte) == 1);

	// Modificare valida
	SRV_modifica(ag, 1, "apartament", 6456.5, "Cluj-Napoca nr.2543", 325);

	Oferta* modificat = get(ag->Oferte, 0);

	assert(strcmp(modificat->tip, "apartament") == 0);
	assert(modificat->suprafata == 6456.5);
	assert(strcmp(modificat->adresa, "Cluj-Napoca nr.2543") == 0);
	assert(modificat->pret == 325);

	// Modificare invalida
	info = SRV_modifica(ag, 1, "apartament", -6456.5, "Cluj-Napoca nr.2543", -325);
	assert(info.cod == 1);
	assert(strcmp(info.text, "Suprafata invalida !\nPret invalid !\n") == 0);
	undo(ag);
	Oferta*  modificat1 = get(ag->Oferte, 0);
	assert(strcmp(modificat1->tip, "casa") == 0);
	assert(modificat1->suprafata == 425.43);
	assert(strcmp(modificat1->adresa, "Cluj-Napoca nr.2") == 0);
	assert(modificat1->pret == 643457.99);
	assert(size(ag->undoList) == 1);
	undo(ag);
	info = undo(ag);
	assert(strcmp(info.text, "Nu se mai poate face undo!\n") == 0);
	destroyAgentie(ag);

}

void test_stergere()
{
	Agentie* ag = creeazaAgentie();
	Informatii info;
	SRV_adauga(ag, "casa", 425.43, "Cluj-Napoca nr.2", 643457.99);
	assert(size(ag->Oferte) == 1);
	SRV_adauga(ag, "apartament", 6456, "Cluj-Napoca nr.2543", 325);
	assert(size(ag->Oferte) == 2);
	SRV_adauga(ag, "teren", 645, "Cluj-Napoca nr.43", 865);
	assert(size(ag->Oferte) == 3);

	// Stergere valida
	info = SRV_stergere(ag, 1);
	assert(info.cod == 0);
	assert(strcmp(info.text, "Comanda realizata cu succes !\n") == 0);
	assert(size(ag->Oferte) == 2);

	info = SRV_stergere(ag, 2);
	assert(info.cod == 0);
	assert(strcmp(info.text, "Comanda realizata cu succes !\n") == 0);
	assert(size(ag->Oferte) == 1);
	//undo(ag);
	//assert(size(ag->undoList) == 2);

	destroyAgentie(ag);

}

void test_ordonare()
{
	Informatii info;
	Agentie* ag = creeazaAgentie();
	Lista* ordonate;
	SRV_adauga(ag, "casa", 425.43, "Cluj-Napoca nr.1", 100000.99);
	SRV_adauga(ag, "teren", 6456, "Cluj-Napoca nr.2", 325);
	SRV_adauga(ag, "apartament", 646, "Cluj-Napoca nr.3", 8768);

	ordonate = copyLista(ag->Oferte, copyOferta);
	info = SRV_ordonate(ordonate, "suprafata", 0);
	assert(info.cod == 1);

	info = SRV_ordonate(ordonate, "pret", 0);
	assert(info.cod == 0);
	assert(get_pret(ordonate->elems[0]) == 325);
	assert(get_pret(ordonate->elems[1]) == 8768);
	assert(get_pret(ordonate->elems[2]) == 100000.99);

	info = SRV_ordonate(ordonate, "tip", -1);
	assert(info.cod == 0);
	assert(strcmp(get_tip(ordonate->elems[0]), "teren") == 0);
	assert(strcmp(get_tip(ordonate->elems[1]), "casa") == 0);
	assert(strcmp(get_tip(ordonate->elems[2]), "apartament") == 0);
	destroyLista(ordonate, destroyOferta);
	destroyAgentie(ag);
}

void test_filtare()
{
	Informatii info;
	Agentie* ag = creeazaAgentie();
	Lista* filtrate;
	SRV_adauga(ag, "casa", 1000.43, "Cluj-Napoca nr.1", 100000.99);
	SRV_adauga(ag, "teren", 6000, "Cluj-Napoca nr.2", 325);

	// Test pt tip
	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "tip", "apartament", -1);
	assert(info.cod == 1);
	assert(strcmp(info.text, "Nu exista oferta care sa satisfaca acest criteriu !\n") == 0);
	assert(size(filtrate) == 0);
	destroyLista(filtrate, destroyOferta);

	filtrate = createLista();
	SRV_adauga(ag, "apartament", 100, "Cluj-Napoca nr.3", 8768);
	info = SRV_filtrare(ag->Oferte, filtrate, "tip", "apartament", -1);
	assert(info.cod == 0);
	assert(size(filtrate) == 1);
	assert(strcmp(get_adr(filtrate->elems[0]), "Cluj-Napoca nr.3") == 0);
	destroyLista(filtrate, destroyOferta);
	
	// Test pt minim suprafata
	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "suprafata", "minima", 1000);
	assert(info.cod == 0);
	assert(size(filtrate) == 2);
	assert(strcmp(get_adr(filtrate->elems[0]), "Cluj-Napoca nr.1") == 0);
	assert(strcmp(get_adr(filtrate->elems[1]), "Cluj-Napoca nr.2") == 0);
	destroyLista(filtrate, destroyOferta);
	// Test pt maxim suprafata
	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "suprafata", "maxima", 1000);
	assert(info.cod == 0);
	assert(size(filtrate) == 1);
	assert(strcmp(get_adr(filtrate->elems[0]), "Cluj-Napoca nr.3") == 0);
	destroyLista(filtrate, destroyOferta);

	// Test pt minim pret
	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "pret", "minima", 8000);
	assert(info.cod == 0);
	assert(size(filtrate) == 2);
	assert(strcmp(get_adr(filtrate->elems[0]), "Cluj-Napoca nr.1") == 0);
	assert(strcmp(get_adr(filtrate->elems[1]), "Cluj-Napoca nr.3") == 0);
	destroyLista(filtrate, destroyOferta);
	// Test pt maxim pret
	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "pret", "maxima", 8000);
	assert(info.cod == 0);
	assert(size(filtrate) == 1);
	assert(strcmp(get_adr(filtrate->elems[0]), "Cluj-Napoca nr.2") == 0);
	destroyLista(filtrate, destroyOferta);

	// Nu exista
	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "pret", "maxima", 10);
	assert(info.cod == 1);
	assert(size(filtrate) == 0);
	destroyLista(filtrate, destroyOferta);

	filtrate = createLista();
	info = SRV_filtrare(ag->Oferte, filtrate, "adresa", "2", 3);
	
	assert(size(filtrate) == 1);
	destroyLista(filtrate, destroyOferta);

	destroyAgentie(ag);
}

void test_cauta()
{
	Agentie* ag = creeazaAgentie();

	SRV_adauga(ag, "casa", 1000.43, "Cluj-Napoca nr.1", 100000.99);
	SRV_adauga(ag, "teren", 6000, "Cluj-Napoca nr.2", 325);
	int x = SRV_cauta(ag, 1, 56);
	assert(x == 0);
	int y = SRV_cauta(ag, 2, 656);
	assert(y == 1);
	int z = SRV_cauta(ag, 5, 56);
	assert(z == -1);

	destroyAgentie(ag);

}



void test_all()
{
	test_creare_si_validare();
	test_adaugare();
	test_modificare();
	test_stergere();
	test_ordonare();
	test_filtare();
	test_cauta();
}
