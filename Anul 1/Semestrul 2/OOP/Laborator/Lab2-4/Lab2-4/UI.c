#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "domain.h"
#include "repo.h"
#include "valid.h"
#include "service.h"

void citire_parametrii(char* tip, double* suprafata, char* adresa, double* pret)
{
	int x;
	printf("Introduceti tipul (teren, casa, apartament): ");
	x = scanf("\n%[^\n]", tip);

	printf("Introduceti suprafata: ");
	x = scanf("%lf", suprafata);

	printf("Introduceti adresa: ");
	x = scanf("\n%[^\n]", adresa);

	printf("Introduceti pretul: ");
	x = scanf("%lf", pret);
}


char* citire_criteriu()
{
	int x;
	char buff[25] = "";
	char* criteriu;
	printf("Introduceti criteriul (tip, suprafata, adresa sau pret): ");
	x = scanf("%s", buff);
	criteriu = malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(criteriu, buff);
	return criteriu;
}

char* citire_criteriu_detalii(char* criteriu, double* numar)
{
	int x;
	char buffer[25] = "";
	if (_stricmp(criteriu, "tip") == 0)
	{
		printf("Introduceti tipul dupa care doriti filtrarea (teren, casa, apartament): ");
		x = scanf("%s", buffer);
		char* tip;
		tip = malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(tip, buffer);
		return tip;
	}
	else if (_stricmp(criteriu, "suprafata") == 0)
	{
		printf("Introduceti suprafata: ");
		x = scanf("%lf", numar);
		printf("Doriti ca aceasta suprafata sa fie cea minima sau cea maxima ?\n");
		x = scanf("%s", buffer);
		char* tip;
		tip = malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(tip, buffer);
		return tip;
	}
	else if (_stricmp(criteriu, "pret") == 0)
	{
		printf("Introduceti pretul: ");
		x = scanf("%lf", numar);
		printf("Doriti ca aceasta suma sa fie cea minima sau cea maxima ?\n");
		x = scanf("%s", buffer);
		char* tip;
		tip = malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(tip, buffer);
		return tip;
	}
	else if (_stricmp(criteriu, "adresa") == 0)
	{

		printf("Dati un substring din adresa: ");
		x = scanf("%s", buffer);

		printf("Dati numarul de oferte care sa se afiseze: \n");
		x = scanf("%lf", numar);

		char* tip;
		tip = malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(tip, buffer);
		return tip;
	}
	else
		return NULL;
}

int citire_ordine()
{
	char ordine[25] = "";
	int x;
	printf("Doriti sa ordonati crescator sau descrescator ?: ");
	x = scanf("%s", ordine);
	if (_stricmp(ordine, "crescator") == 0)
		return 0;
	if (_stricmp(ordine, "descrescator") == 0)
		return -1;
	return 1;
}

void UI_adauga(Agentie* ag)
{
	char tip[20];
	double suprafata;
	char adresa[50];
	double pret;
	citire_parametrii(tip, &suprafata, adresa, &pret);

	Informatii info;
	info = SRV_adauga(ag, tip, suprafata, adresa, pret);
	printf("\n%s", info.text);
}

void UI_modifica(Agentie* ag)
{
	int x, id;

	printf("Introduceti ID-ul ofertei pe care doriti sa o modificati: ");
	x = scanf("%d", &id);
	//|| id >= sizeRepo(ag->allOferts) + 1
	if (id <= 0 )
	{
		printf("ID invalid !\n");
		return;
	}

	char tip[20];
	double suprafata;
	char adresa[50];
	double pret;
	citire_parametrii(tip, &suprafata, adresa, &pret);

	Informatii info;
	info = SRV_modifica(ag, id, tip, suprafata, adresa, pret);
	printf("\n%s", info.text);
}

void UI_stergere(Agentie* ag)
{
	int x, id;

	printf("Introduceti ID-ul ofertei pe care doriti sa o stergeti: ");
	x = scanf("%d", &id);
	//|| id >= size(repo) + 1
	if (id <= 0)
	{
		printf("ID invalid !\n");
		return;
	}

	Informatii info;
	info = SRV_stergere(ag, id);
	printf("\n%s", info.text);
 }

void UI_afisare(Lista* l)
{
	int i;
	if (size(l) == 0)
		printf("Nu exista oferte ! Folositi optiunea '1' pentru a adauga oferte !\n");
	else
	{
		printf("Ofertele sunt: \n\n");
		for (i = 0; i < size(l); i++)
		{
			Oferta* o = get(l, i);
			//printf("%d.  %s %.2lf %s %.2lf\n",(i+1), o->tip, o->suprafata, o->adresa, o->pret);
			printf("%d. Tip: %s, Suprafata: %.2lf, Adresa: %s, Pret: %.2lf\n", (i + 1), o->tip, o->suprafata, o->adresa, o->pret);
		}
	}

}

void UI_ordonare(Agentie* ag)
{
	if (size(ag->Oferte) == 0)
	{
		printf("Nu exista oferte ! Folositi optiunea '1' pentru a adauga oferte !\n");
		return;
	}
	char* criteriu = citire_criteriu();
	if (!validare_criteriu(criteriu))
	{
		printf("Criteriu inexistent !\n");
		free(criteriu);
		return;
	}
	int ordine = citire_ordine();
	if (ordine == 1)
	{
		printf("Ordinea poate fi doar 'crescator' sau 'descrescator' !\n");
		free(criteriu);
		return;
	}

	Lista* ordonate = copyLista(ag->Oferte, copyOferta);
	Informatii info;

	info = SRV_ordonate(ordonate, criteriu, ordine);
	if (info.cod)
	{
		printf("\n%s", info.text);
		destroyLista(ordonate, destroyOferta);
		free(criteriu);
		return;
	}
	UI_afisare(ordonate);
	destroyLista(ordonate, destroyOferta);
	free(criteriu);
}

void UI_filtrare(Agentie* ag)
{
	if (size(ag->Oferte) == 0)
	{
		printf("Nu exista oferte ! Folositi optiunea '1' pentru a adauga oferte !\n");
		return;
	}
	char* criteriu = citire_criteriu();
	if (!validare_criteriu(criteriu))
	{
		printf("Criteriu inexistent !\n");
		free(criteriu);
		return;
	}
	char* tip = NULL;
	double nr = -1;
	tip = citire_criteriu_detalii(criteriu, &nr);
	if (_stricmp(criteriu, "tip") == 0 && !validare_tip(tip))
	{
		printf("Tip inexistent !\n");
		free(criteriu);
		return;
	}
	if ((_stricmp(criteriu, "pret") == 0 || _stricmp(criteriu, "suprafata") == 0) && !(_stricmp(tip, "minima") == 0 || _stricmp(tip, "maxima") == 0))
	{
		printf("Limita invalida !\n");
		free(criteriu);
		free(tip);
		return;
	}

	Lista* filtrate = createLista();
	Informatii info;

	info = SRV_filtrare(ag->Oferte, filtrate, criteriu, tip, nr);
	
	if (info.cod)
	{
		printf("\n%s", info.text);
		free(tip);
		free(criteriu);
		destroyLista(filtrate, destroyOferta);
		return;
	}
	UI_afisare(filtrate);
	free(criteriu);
	free(tip);
	destroyLista(filtrate, destroyOferta);
}

void UI_undo(Agentie* ag)
{
	Informatii info;
	info = undo(ag);
	if (info.cod==1)
	{
		printf("\n%s", info.text);
		return;
	}
}

void UI_funct(Agentie* ag)
{
	int id;
	int pret;
	printf("Introduceti ID-ul ofertei pe care doriti sa o cautati: ");
	scanf("%d", &id);
	if (id <= 0)
	{
		printf("ID invalid !\n");
		return;
	}
	printf("Dati un pret:");
	scanf_s("%d", &pret);

	int x = SRV_cauta(ag, id, pret);
	if (x == 1)
		{
			printf("Pretul ofertei este mai mic decat cel introdus\n");
			return;
		}
	else if (x==0)
		{
			printf("Pretul ofertei este mai mare decat cel introdus\n");
			return;
		}
	else if (x == -1)
	{
		printf("Oferta neexistenta!\n");
		return;
	}

}


// Functia care afiseaza meniul
void help()
{
	printf("Agentie imobiliara [Version 1.0.450]\n");
	printf("(c)2021 Delta Corporation. All rights reserved.\n\n");
	printf("=-=-=-=-=-Meniu-=-=-=-=-=\n");
	printf("1. Adaugare oferta\n");
	printf("2. Actualizare oferta\n");
	printf("3. Stergere oferta\n");
	printf("4. Vizualizare oferete ordonat dupa pret, tip\n");
	printf("5. Vizualizare oferta filtrate dupa un criteriu (tip, suprafata, pret, adresa)\n");
	printf("6. Undo\n");
	printf("7. oferta+pret \n");
	printf("9. Vizualizare oferte\n");
	printf("0. Iesire din aplicatie\n");
}

// Functia principala care citeste comanda si executa apeleaza functiile necesare rezolvarii acesteia
void run()
{
	//Lista* lista = createLista();
	Agentie* ag = creeazaAgentie();

	int running = 1, x;
	char cmd[250] = "";

	while (running)
	{
		help();
		printf(">>>");
		x = scanf("%s", cmd);
		if (strcmp(cmd, "0") == 0)
		{
			running = 0;
			printf("Sayonara !\n");
		}
		else if (strcmp(cmd, "1") == 0)
			UI_adauga(ag);
		else if (strcmp(cmd, "2") == 0)
		{
			UI_afisare(ag->Oferte);
			if (size(ag->Oferte) != 0)
				UI_modifica(ag);
		}
		else if (strcmp(cmd, "3") == 0)
		{
			UI_afisare(ag->Oferte);
			if (size(ag->Oferte) != 0)
				UI_stergere(ag);
		}
		else if (strcmp(cmd, "4") == 0)
			UI_ordonare(ag);
		else if (strcmp(cmd, "5") == 0)
			UI_filtrare(ag);
		else if (strcmp(cmd, "9") == 0)
			UI_afisare(ag->Oferte);
		else if (strcmp(cmd, "6") == 0)
			UI_undo(ag);
		else if (strcmp(cmd, "7") == 0)
			UI_funct(ag);
		else
			printf("Comanda invalida !\n");
		system("pause");
		system("cls");
	}
	destroyAgentie(ag);
}

//void run_cu_nr()
//{
//	Repo repo;
//	repo.n = 0;
//	int running = 1, cmd, x;
//
//	while (running)
//	{
//		help();
//		printf(">>>");
//		x = scanf("%d", &cmd);
//		switch (cmd)
//		{
//		case 0:
//			running = 0;
//			printf("Sayonara !\n");
//			break;
//		case 1:
//			UI_adauga(&repo);
//			break;
//		case 2:
//			UI_afisare(&repo);
//			if (repo.n != 0)
//				UI_modifica(&repo);
//			break;
//		case 3:
//			UI_afisare(&repo);
//			if (repo.n != 0)
//				UI_stergere(&repo);
//			break;
//		case 9:
//			UI_afisare(&repo);
//			break;
//		default:
//			printf("Comanda invalida !\n");
//			break;
//		}
//		system("pause");
//		system("cls");
//	}
//}