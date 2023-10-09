#define INIT_CAPACITY 2
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "repo.h"
#include "domain.h"

#include <assert.h>


Repository createRepo()
{
	Repository repo;
	repo.lg = 0;
	repo.capacity = INIT_CAPACITY;
	repo.elems = malloc(sizeof(ElemType)* INIT_CAPACITY);
	return repo;
}

void destroyRepo(Repository* r)
{

	for (int i = 0; i < r->lg; i++)
	{
		destroy_med(&r->elems[i]);
	}
	free(r->elems);
	r->elems = NULL;
	r->lg = 0;
}

ElemType get(Repository* r, int poz)
{
	return r->elems[poz];
}

ElemType set(Repository* r, int poz, Medicine med)
{
	ElemType rez = r->elems[poz];
	r->elems[poz] = med;
	return rez;
}


int len(Repository* r)
{
	return r->lg;
}


void ensure_capacity(Repository* r)
{
	int newCap = 2 * r->capacity;
	ElemType* nElems = malloc(newCap * sizeof(ElemType));
	for (int i = 0; i < len(r); i++)
	{
		nElems[i] = r->elems[i];
	}
	free(r->elems);
	r->elems = nElems;
	r->capacity = newCap;
}

void add_repo(Repository* r, ElemType el)
{
	if (len(r) == r->capacity)
	{
		ensure_capacity(r);
	}
	r->elems[r->lg] = el;
	r->lg++;
}

Repository copyRep(Repository* r)
{
	Repository rez = createRepo();
	for (int i = 0; i < len(r); i++)
	{
		ElemType med = get(r, i);
		add_repo(&rez, copyMed(&med));
	}

	return rez;

}


int find(Repository* r, int code)
{
	for (int i = 0; i < len(r); i++)
	{
		if (r->elems[i].code == code)
			return 1;
	}
	return 0;
}


void update_repo(Repository* r, int code, char* name, float concentration)
{
	for (int i = 0; i < len(r); i++)
	{
		if (r->elems[i].code == code)
		{
			strcpy_s(r->elems[i].name, strlen(name) + 1, name);
			r->elems[i].concentration = concentration;
		
		}
	}
}

void update_quantity_r(Repository* r, int code, int quantity)
{
	for (int i = 0; i < len(r); i++)
	{
		if (r->elems[i].code == code)
		{
			r->elems[i].quantity += quantity;
		}
	}
}

void sort(Repository* r, int opt1, FunctieComparare cmpF)
{
 	for (int j = 1; j < len(r); j++)
		for (int i = 0; i < len(r) - j; i++)
		{
			Medicine m1 = get(r, i);
			Medicine m2 = get(r, i + 1);
			if (opt1 == 1)
			{
				if (cmpF(&m1, &m2) > 0)
				{
					set(r, i, m2);
					set(r, i + 1, m1);
				}
			}
			else if (opt1 == 2)
			{
				if (cmpF(&m1, &m2) < 0)
				{
					set(r, i, m2);
					set(r, i + 1, m1);
				}
			}
		}
}


void test_repo()
{
	Repository repo = createRepo();
	assert(len(&repo) == 0);
	add_repo(&repo, create_medicine(11, "Nurofen", 23, 8));
	add_repo(&repo, create_medicine(17, "Ibusinus", 20, 3));
	add_repo(&repo, create_medicine(25, "Vitamina C", 25, 10));
	assert(len(&repo) == 3);

	Repository rez = copyRep(&repo);
	assert(len(&rez) == 3);
	destroyRepo(&rez);

	Medicine med = get(&repo, 0);
	assert(strcmp(med.name, "Nurofen") == 0);
	med = get(&repo, 1);
	assert(med.concentration == 20);

	Medicine new_med = create_medicine(15, "Ascovit", 55, 9);
	med = get(&repo, 2);
	destroy_med(&med);
	med = set(&repo, 2, new_med);

	med = get(&repo, 2);
	assert(med.code == 15);
	assert(med.concentration == 55);
	

	assert(find(&repo, 17) == 1);
	assert(find(&repo, 178) == 0);

	update_quantity_r(&repo, 11, 5);
	med = get(&repo, 0);
	assert(med.quantity == 13);

	update_repo(&repo, 11, "Tantum", 11);
	assert(strcmp(get(&repo, 0).name, "Tantum") == 0);
	assert(get(&repo, 0).concentration == 11);

	destroyRepo(&repo);
	assert(len(&repo) == 0);
}
