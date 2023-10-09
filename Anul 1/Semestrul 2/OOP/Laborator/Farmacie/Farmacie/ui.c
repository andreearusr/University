#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "domain.h"
#include "service.h"
#include "repo.h"

void add_ui(MedStore* store)
{
	char name[100];
	int code, quantity;
	float concentration;

	printf("Dati codul unic al medicamentului: ");
	scanf_s("%d", &code);
	if (code < 0)
	{
		printf("Cod medicament invalid!\n");
		return;
	}

	else
	{
		int ok = find_m(store, code);
		if (ok == 1)
		{
			printf("Medicamentul exista deja in stoc!\n");
			printf("Se adauga o noua cantitate la cea existenta\n");
			printf("Dati cantitatea:");
			scanf_s("%d", &quantity);
			if (quantity < 0)
			{
				printf("Cantitate medicament invalida!\n");
				return;
			}
			else
			{
				update_quantity(store, code, quantity);
			}
		}

		else
		{
			printf("Dati numele medicamentului: ");
			scanf_s("%s", name, 100);
			printf("Dati concentratia medicamentului: ");
			scanf_s("%f", &concentration);
			printf("Dati cantitatea medicamentului: ");
			scanf_s("%d", &quantity);
			int err = add_medicine(store, code, name, concentration, quantity);
			if (err == 0)
			{
				printf("Medicament adaugat cu succes!\n");
				return;
			}
			else
			{
				printf("Medicament invalid!\n");
				return;
			
			}
			
		}
	}
}


void print_ui(Repository* r)
{
	printf("\nLista de medicamente:\n");
	for (int i=0; i< len(r); i++)
	{
		Medicine med = get(r, i);
		printf("Cod:%d  Nume:%s  Concentratie:%f  Cantitate:%d\n", med.code, med.name, med.concentration, med.quantity);
	}
	printf("\n");
}

void showall(MedStore* store)
{
	Repository r = getallMed(store);
	print_ui(&r);
	destroyRepo(&r);
}


void update_ui(MedStore* store)
{
	char name[100];
	int code;
	float concentration;

	printf("Dati codul unic al medicamentului: ");
	scanf_s("%d", &code);
	if (code < 0)
	{
		printf("Cod medicament incorect!\n");
		return;
	}
	else
	{
		int ok = find_m(store, code);
		if (ok == 1)
		{
			printf("Dati numele nou al  medicamentului: ");
			scanf_s("%s", name, 100);
			printf("Dati concentratia noua a medicamentului: ");
			scanf_s("%f", &concentration);
			if (concentration < 0 || concentration > 100)
			{
				printf("Concentratie medicament invalida!\n");
				return;
			}
			update_medicine(store, code, name, concentration);

		}
		else
		{
			printf("Medicament neexistent in stoc!\n");
		}
	}
}


void delete_ui(MedStore* store)
{
	int code;
	printf("Dati codul unic al medicamentului: ");
	scanf_s("%d", &code);
	if (code < 0)
	{
		printf("Cod medicament invalid!\n");
		return;
	}
	else
	{
		int ok = find_m(store, code);
		if (ok == 1)
		{
			delete_medicine(store, code);
		}
		else
		{
			printf("Medicament neexistent in stoc!\n");
		}
	}
	
}

void sort_ui(MedStore* store)
{
	int opt,opt1;
	printf("1. Ordonare dupa nume\n2. Ordonare dupa cantitate\n");
	printf("Dati optiunea:");
	scanf_s("%d", &opt);
	if (opt == 1)
	{
		printf("1. Crescator\n2. Descrescator\n");
		printf("Dati optiunea:");
		scanf_s("%d", &opt1);
		if (opt1 == 1 || opt1 == 2)
		{
			Repository rez = sort_name(store, opt1);
			print_ui(&rez);
			destroyRepo(&rez);
		}
		else
		{
			printf("Optiune invalida!\n");
			return;
		}
	}
	else if (opt == 2)
	{
		printf("1. Crescator\n2. Descrescator\n");
		printf("Dati optiunea:");
		scanf_s("%d", &opt1);
		if (opt1 == 1 || opt1 == 2)
		{
			Repository rez = sort_quantity(store, opt1);
			print_ui(&rez);
			destroyRepo(&rez);
		}
		else
		{
			printf("Optiune invalida!\n");
			return;
		}
	}
	else
	{
		printf("Optiune invalida!\n");
		return;
	}

}


void filter_ui(MedStore* store)
{
	int opt;
	printf("1. Filtrare dupa cantitate\n2. Filtrare dupa prima litera din nume\n");
	printf("Dati optiunea:");
	scanf_s("%d", &opt);
	if (opt == 1)
	{
		int cant;
		printf("Dati cantitatea:");
		scanf_s("%d", &cant);
		if (cant < 0)
		{
			printf("Cantitate invalida!\n");
			return;
		}
		else
		{
			Repository rez = filter_quantity(store, cant);
			print_ui(&rez);
			destroyRepo(&rez);
		}
	}
	else if (opt == 2)
	{
		char lit;
		printf("Dati prima litera:");
		getchar();
		scanf("%c", &lit);
		Repository rez = filter_name(store, lit);
		print_ui(&rez);
		destroyRepo(&rez);
	}
	else
	{
		printf("Optiune invalida!\n");
		return;
	}

}



void run_all_tests()
{
	test_domain();
	test_repo();
	test_service();

	test_sort();
	test_filter();
	test_update();
}


void menu()
{
	printf("\tGestiune farmacie\n");
	printf("1. Adaugare medicament nou\n");
	printf("2. Actualizare medicament\n");
	printf("3. Stergere stoc medicament\n");
	printf("4. Sortare medicamente din stoc\n");
	printf("5. Filtrare medicamente\n");
	printf("6. Afisare lista medicamente\n");
	printf("7. Iesire\n");
}

void run()
{
	MedStore store = createMedStore();
	int cmd = 0;
	while (1)
	{
		menu();
		printf("Alegeti optiunea: ");
		scanf_s("%d", &cmd);
		if (cmd == 1)
			add_ui(&store);
		else if (cmd == 2)
			update_ui(&store);
		else if (cmd == 3)
			delete_ui(&store);
		else if (cmd == 4)
			sort_ui(&store);
		else if (cmd == 5)
			filter_ui(&store);
		else if (cmd == 6)
			showall(&store);

		else if (cmd == 7)
		{
			printf("Goodbye");
			break;
		}
		else
		{
			printf("Comanda invalida!\n");
		}

	}
	destroyStore(&store);

}

