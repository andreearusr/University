
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <assert.h>

#include "service.h"
#include "repo.h"
#include "domain.h"

MedStore createMedStore()
{
	MedStore rez;
	rez.allMed = createRepo();
	return rez;
}

void destroyStore(MedStore* store)
{
	destroyRepo(&store->allMed);
}


int add_medicine(MedStore* store, int code , char* name, float concentration, int quantity)
{
	Medicine med = create_medicine(code, name, concentration, quantity);

	int err = validate_med(med);
	if (err != 0)
	{
		destroy_med(&med);
		return err;
	}

	add_repo(&store->allMed, med);
	return 0;
}

Repository getallMed(MedStore* store)
{
	Repository rez = createRepo();
	for (int i = 0; i < len(&store->allMed); i++)
	{
		Medicine med = get(&store->allMed, i);
		add_repo(&rez, copyMed(&med));
	}
	return rez;
}


int find_m(MedStore* store, int code)
{
	return find(&store->allMed,code);
}


void update_quantity(MedStore* store, int code, int quantity)
{
	update_quantity_r(&store->allMed, code, quantity);
}

void delete_medicine(MedStore* store, int code)
{
	for (int i = 0; i < len(&store->allMed); i++)
	{
		if (store->allMed.elems[i].code == code)
			store->allMed.elems[i].quantity = 0;
	}
}


void update_medicine(MedStore* store, int code, char* name, float concentration)
{
	update_repo(&store->allMed, code, name, concentration);
}

int cmpName(Medicine* m1, Medicine* m2) {

	return strcmp(m1->name, m2->name);
}


Repository sort_name(MedStore* store, int opt1)
{
	Repository rez = copyRep(&store->allMed);
	sort(&rez, opt1, cmpName);
	return rez;


	/*
	if (opt1 == 1)
	{
		for (int i = 0; i < len(&rez); i++)
			for (int j = i + 1; j < len(&rez); j++)
			{
				Medicine m1 = get(&rez, i);
				Medicine m2 = get(&rez, j);
				if (strcmp(m1.name, m2.name) > 0)
				{
					set(&rez, i, m2);
					set(&rez, j, m1);
				}
			}
	}

	else if(opt1==2)
	{
		for (int i = 0; i < len(&rez); i++)
			for (int j = i + 1; j < len(&rez); j++)
			{
				Medicine m1 = get(&rez, i);
				Medicine m2 = get(&rez, j);
				//Medicine aux;
				if (strcmp(m1.name, m2.name) < 0)
				{
					set(&rez, i, m2);
					set(&rez, j, m1);
				}

			}
	}

	return rez;
	*/
	}

int cmpQuantity(Medicine* m1, Medicine* m2) {

	if (m1->quantity < m2->quantity)
	{
		return -1;}
	
	else if (m1->quantity > m2->quantity)
	{
		return 1;}
	return 0;
}

Repository sort_quantity(MedStore* store, int opt1)
{

	Repository rez = copyRep(&store->allMed);
	sort(&rez, opt1, cmpQuantity);
	return rez;

   /*
	if (opt1 == 1)
	{
		for (int i = 0; i < len(&rez); i++)
			for (int j = i + 1; j < len(&rez); j++)
			{
				Medicine m1 = get(&rez, i);
				Medicine m2 = get(&rez, j);
				if (m1.quantity > m2.quantity)
				{
					set(&rez, i, m2);
					set(&rez, j, m1);
				}
			}
	}
	else if (opt1 == 2)
	{
		for (int i = 0; i < len(&rez); i++)
			for (int j = i + 1; j < len(&rez); j++)
			{
				Medicine m1 = get(&rez, i);
				Medicine m2 = get(&rez, j);
				if (m1.quantity < m2.quantity)
				{
					set(&rez, i, m2);
					set(&rez, j, m1);
				}
			}
	}
	return rez;
	*/
	}

Repository filter_quantity(MedStore* store, int quantity)
{
	Repository rez = createRepo();
	for (int i = 0; i < store->allMed.lg; i++)
	{
		Medicine med = get(&store->allMed, i);
		if(med.quantity < quantity)
		{
			add_repo(&rez, copyMed(&med));
		}

	}

	return rez;

}

Repository filter_name(MedStore* store, char lit)
{
	Repository rez = createRepo();
	for (int i = 0; i < store->allMed.lg; i++)
	{
		Medicine med = get(&store->allMed, i);
		if (med.name[0] == lit)
		{
			add_repo(&rez, copyMed(&med));
		}
	}
	return rez;
}


void test_service()
{
	MedStore store = createMedStore();
	//store.allMed = createRepo();
	add_medicine(&store, 12, "Vitamina C", 23, 7);
	add_medicine(&store, 20, "Ascovit", 19, 3);
	add_medicine(&store, 11, "Parasinus", 31, 10);

	int ok = add_medicine(&store, -3, "Ascovit", 19, 3);
	assert(ok == 1);
	int ok1 = add_medicine(&store, 3, "", 19, 3);
	assert(ok1 == 2);
	int ok2 = add_medicine(&store, 7, "Ascovit", -6, 3);
	assert(ok2 == 3);
	int ok3 = add_medicine(&store, 7, "Ascovit", 6, -93);
	assert(ok3 == 4);

	Repository rez = getallMed(&store);
	assert(len(&rez) == 3);
	destroyRepo(&rez);
	
	assert(find_m(&store, 11) == 1);
	assert(find_m(&store, 45) == 0);
	
	Medicine med = get(&store.allMed, 1);
	assert(strcmp(med.name,"Ascovit")==0);
	assert(med.concentration == 19 );
	assert(med.quantity == 3);

	delete_medicine(&store, 20);
	Medicine med1 = get(&store.allMed, 1);
	assert(med1.quantity == 0);

	update_quantity(&store, 20, 5);
	Medicine med2 = get(&store.allMed, 1);
	assert(med2.quantity == 5);

	destroyStore(&store);
}


void test_sort()
{
	MedStore store = createMedStore();
	add_medicine(&store, 11, "Parasinus", 31, 10);
	add_medicine(&store, 20, "Ascovit", 19, 3);
	add_medicine(&store, 12, "VitaminaC", 23, 7);
	add_medicine(&store, 13, "Sindolor", 4, 3);


	Repository r = sort_name(&store,1);
	assert(strcmp(get(&r, 0).name, "Ascovit") == 0);
	destroyRepo(&r);

	r = sort_name(&store, 2);
	assert(strcmp(get(&r, 0).name, "VitaminaC") == 0);
	destroyRepo(&r);

	
	r = sort_quantity(&store, 1);
	assert(strcmp(get(&r, 0).name, "Ascovit") == 0);
	destroyRepo(&r);

	r = sort_quantity(&store, 2);
	assert(strcmp(get(&r, 0).name, "Parasinus") == 0);
	destroyRepo(&r);
	
	destroyStore(&store);
}


void test_filter()
{
	MedStore store = createMedStore();
	add_medicine(&store, 11, "Parasinus", 31, 10);
	add_medicine(&store, 20, "Ascovit", 19, 3);
	add_medicine(&store, 12, "VitaminaC", 23, 7);

	Repository r = filter_quantity(&store, 8);
	assert(len(&r)==2);
	destroyRepo(&r);

	Repository r2 = filter_name(&store, 'V');
	assert(len(&r2) == 1);
	destroyRepo(&r2);

	destroyStore(&store);

}

void test_update()
{
	MedStore store = createMedStore();
	add_medicine(&store, 11, "Parasinus", 31, 10);
	add_medicine(&store, 20, "Ascovit", 19, 3);
	add_medicine(&store, 12, "VitaminaC", 23, 7);

	update_medicine(&store, 11, "Tantum", 11);
	assert(strcmp(get(&store.allMed, 0).name, "Tantum") == 0);
	assert(get(&store.allMed, 0).concentration == 11);

	destroyStore(&store);
}