#include <string.h>
#include "domain.h"
#include "repo.h"
#include "valid.h"
#include "sort.h"
#include "service.h"
#include <malloc.h>

Agentie* creeazaAgentie()
{
	Agentie* ag = malloc(sizeof(Agentie));
	ag->Oferte = createLista();
	ag->undoList = createLista();
	return ag;
}

void destroyAgentie(Agentie* ag)
{
	destroyLista(ag->Oferte, destroyOferta);
	destroyLista(ag->undoList, destroyListaOferte);
	free(ag);
}


Informatii SRV_adauga(Agentie* ag, char* tip, double suprafata, char* adresa, double pret)
{
	Oferta* oferta = createOferta(tip, suprafata, adresa, pret);
	//Lista* listUndo = copyLista(ag->allOferts->lista, copyOferta);

	Informatii info;
	info = validare(oferta);
	if (info.cod != 0)
	{
		destroyOferta(oferta);
		return info;
	}
	int i;

	for (i = 0; i < size(ag->Oferte); i++)
	{
		if (strcmp(get_adr(ag->Oferte->elems[i]), oferta->adresa) == 0)
		{
			info.cod = 2;
			strcpy(info.text, "Oferta deja existenta la aceasta adresa !\n");
			destroyOferta(oferta);
			return info;
		}
	}

	add(ag->undoList, copyLista(ag->Oferte, copyOferta));
	add(ag->Oferte, oferta);
	return info;
}

Informatii SRV_modifica(Agentie* ag, int id, char* tip, double suprafata, char* adresa, double pret)
{
	Informatii info;
	Oferta* ofertaNoua = createOferta(tip, suprafata, adresa, pret);
	//Lista* listUndo = copyLista(ag->allOferts->lista, copyOferta);

	info = validare(ofertaNoua);
	if (info.cod == 1)
	{
		destroyOferta(ofertaNoua);
		return info;
	}
	strcpy(info.text, "Comanda realizata cu succes !\n");
	info.cod = 0;

	add(ag->undoList, copyLista(ag->Oferte, copyOferta));
	destroyOferta(ag->Oferte->elems[id - 1]);
	set(ag->Oferte, id - 1, ofertaNoua);

	//ag->Oferte->elems[id - 1] = ofertaNoua;
	return info;
}

Informatii SRV_stergere(Agentie* ag, int id)
{
	Informatii info;
	//Lista* listUndo = copyLista(ag->allOferts->lista, copyOferta);
	strcpy(info.text, "Comanda realizata cu succes !\n");
	info.cod = 0;

	//destroyOferta(&repo->elems[id - 1]);

	//if (id == size(repo))
	//{
	//	repo->lg -= 1;
	//	return info;
	//}
	//int i;

	//for (i = id - 1; i < size(repo) - 1; i++)
	//{
	//	Oferta next = get(repo, i + 1);
	//	set(repo, i, next);
	//	//repo->elems[i] = repo->elems[i + 1];
	//}
	//repo->lg -= 1;


	add(ag->undoList, copyLista(ag->Oferte, copyOferta));
	del(ag->Oferte, id - 1);
	return info;
}

double cmpTip(Oferta* p1, Oferta* p2) {
	return (double)_stricmp(p1->tip, p2->tip);
}

double cmpPret(Oferta* p1, Oferta* p2) {
	return p1->pret - p2->pret;
}

Informatii SRV_ordonate(Lista* l, char* criteriu, int ordine)
{
	Informatii info;
	strcpy(info.text, "Comanda realizata cu succes !\n");
	info.cod = 0;
	if (_stricmp(criteriu, "pret") == 0)
		sort(l, cmpPret, ordine);
	else if (_stricmp(criteriu, "tip") == 0)
		sort(l, cmpTip, ordine);
	else
	{
		strcpy(info.text, "Imi pare rau, nu am fost programat sa sortez dupa acest criteriu ! :(\n");
		info.cod = 1;
	}
	return info;
}

//Informatii SRV_ordonate_old(Lista* repo, char* criteriu, int ordine)
//{
//	Informatii info;
//	strcpy(info.text, "Comanda realizata cu succes !\n");
//	info.cod = 0;
//	if (_stricmp(criteriu, "pret") == 0)
//	{
//		int i, j;
//		for (i = 0; i < size(repo) - 1; i++)
//			for (j = i + 1; j < size(repo); j++)
//				if ((repo->elems[i].pret > repo->elems[j].pret && ordine == 0) || (repo->elems[i].pret < repo->elems[j].pret && ordine == -1))
//				{
//					Oferta aux = repo->elems[i];
//					repo->elems[i] = repo->elems[j];
//					repo->elems[j] = aux;
//				}
//	}
//	else if (_stricmp(criteriu, "tip") == 0)
//	{
//		int i, j;
//		for (i = 0; i < size(repo) - 1; i++)
//			for (j = i + 1; j < size(repo); j++)
//				if ((_stricmp(repo->elems[i].tip, repo->elems[j].tip) > 0 && ordine == 0) || (_stricmp(repo->elems[i].tip, repo->elems[j].tip) < 0 && ordine == -1))
//				{
//					Oferta aux = repo->elems[i];
//					repo->elems[i] = repo->elems[j];
//					repo->elems[j] = aux;
//				}
//	}
//	else
//	{
//		strcpy(info.text, "Imi pare rau, nu am fost programat sa sortez dupa acest criteriu ! :(\n");
//		info.cod = 1;
//	}
//	return info;
//}


Informatii SRV_filtrare(Lista* l, Lista* f, char* criteriu, char* tip, double nr)
{
	Informatii info;
	strcpy(info.text, "Comanda realizata cu succes !\n");
	info.cod = 0;
	int i;
	for (i = 0; i < l->lg; i++)
		if (_stricmp(criteriu, "tip") == 0)
		{
			if (_stricmp(tip, get_tip(l->elems[i])) == 0)
				add(f, copyOferta(l->elems[i]));
		}
		else if (_stricmp(criteriu, "suprafata") == 0)
		{
			if (_stricmp(tip, "maxima") == 0)
			{
				if (get_suprafata(l->elems[i]) <= nr)
					add(f, copyOferta(l->elems[i]));
			}
			else if (_stricmp(tip, "minima") == 0)
				if (get_suprafata(l->elems[i]) >= nr)
					add(f, copyOferta(l->elems[i]));
		}
		else if (_stricmp(criteriu, "pret") == 0)
		{
			if (_stricmp(tip, "maxima") == 0)
			{
				if (get_pret(l->elems[i]) <= nr)
					add(f, copyOferta(l->elems[i]));
			}
			else if (_stricmp(tip, "minima") == 0)
				if (get_pret(l->elems[i]) >= nr)
					add(f, copyOferta(l->elems[i]));
		}

		else if (_stricmp(criteriu, "adresa") == 0)
		{
			int count = 0;
			if (nr !=  count )
			{
				if ( strstr(get_adr(l->elems[i]), tip) != NULL)
				{
					add(f, copyOferta(l->elems[i]));
					count++;
				}
			}

		}

	if (size(f) == 0)
	{
		info.cod = 1;
		strcpy(info.text, "Nu exista oferta care sa satisfaca acest criteriu !\n");
	}
	return info;
}

Informatii undo(Agentie* ag)
{	
	//Lista* copie = copyLista(ag->Oferte, copyOferta);

	Informatii info;
	info.cod = 0;
	if (size(ag->undoList) != 0)
	{
		Lista* lAux = destroyUltim(ag->undoList);
		destroyLista(ag->Oferte, destroyOferta);
		ag->Oferte = lAux;
	}
	else
	{
		strcpy(info.text, "Nu se mai poate face undo!\n");
		info.cod = 1;
	}
	return info;

}


int SRV_cauta(Agentie* ag, int id, int pret)
{
	if (id > ag->Oferte->lg)
		return -1;

	Oferta* o = get(ag->Oferte, id - 1);
	if (o->pret/o->suprafata < pret)
		return 1;
	return 0;
}
