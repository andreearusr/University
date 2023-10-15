#include "Teste.h"
#include "Abonament.h"
#include"Repository.h"
#include"Service.h"
#include <assert.h>

void test()
{
	Abonament a = Abonament("Andreea", "aa", 34, 2);
	assert(a.get_nume() == "Andreea");
	assert(a.get_tip() == "aa");
	assert(a.get_pret() == 34);
	assert(a.get_numar() == 2);

	Repository r{ "test.txt" };
	Service srv{ r };

	assert(srv.get_all().size() == 2);

	vector<Abonament> rez = srv.sortare();
	assert(rez[0].get_nume() == "Mihai");

}

void testare() {
	test();
}