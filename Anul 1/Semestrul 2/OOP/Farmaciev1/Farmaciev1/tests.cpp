
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validare.h"
#include <assert.h>

#include "Reteta.h"


void test_domain()
{
	Medicament med = Medicament("Nurofen", "Reckitt", "Ibuprofen", 32.5);
	assert(med.get_denumire() == "Nurofen");
	assert(med.get_producator() == "Reckitt");
	assert(med.get_substanta() == "Ibuprofen");
	assert(med.get_pret() == 32.5);
}



void test_repo() {

	Repository r;
	r.add_medicament(Medicament("VitaminaC", "Bayer", "acid ascorbic", 22));
	r.add_medicament(Medicament("Aspirina", "Carl", "acid acetilsalicilic", 15));
	assert(r.get_all().size() == 2);

	try {
		r.add_medicament(Medicament("VitaminaC", "aaa", "acid", 34));
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	Medicament m = r.find("VitaminaC");
	assert(m.get_denumire() == "VitaminaC");

	try {
		r.find("Ascovit");
		assert(false);
	}
	catch (const RepoException& ex)
	{
		assert(ex.getMessage() == "Medicamentul nu exista in stoc!\n");
	}

	assert(RepoException("dadada").getMessage() == "dadada");

	r.delete_medicament("VitaminaC");
	assert(r.get_all().size() == 1);
	Medicament med = r.get(0);
	assert(med.get_denumire() == "Aspirina");
	assert(med.get_producator() == "Carl");
	assert(med.get_substanta() == "acid acetilsalicilic");
	assert(med.get_pret() == 15);


	try {
		r.delete_medicament("VitaminaC");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}


	r.update_medicament("Aspirina", Medicament("Ibusinus", "Laropharm", "ibuprofen", 35));
	med = r.get(0);
	assert(med.get_denumire() == "Ibusinus");
	assert(med.get_producator() == "Laropharm");
	assert(med.get_substanta() == "ibuprofen");
	assert(med.get_pret() == 35);

	try {
		r.update_medicament("VitaminaC", Medicament("Ibusinus", "Laropharm", "ibuprofen", 35));
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	r.add_medicament(Medicament("aaa", "eee", "acid ", 11));
	r.add_medicament(Medicament("bbb", "ddd",  "ascorbic", 45));
	r.add_medicament(Medicament("ccc", "ccc", "ibuprofen", 33));
	r.add_medicament(Medicament("ddd", "bbb", "acid acetilsalicilic", 14));
	r.add_medicament(Medicament("eee", "aaa", "ibuprofen", 22));
	assert(r.get_all().size() == 6);
}



void test_service() {

	Repository r;
	Validator valid;
	Reteta reteta{ r };
	Service srv{ r, valid , reteta};
	srv.add_medicament(Medicament("VitaminaC", "Bayer", "acid ascorbic", 22));
	srv.add_medicament(Medicament("Aspirina", "Carl", "acid acetilsalicilic", 15));
	assert(srv.get_all().size() == 2);


	srv.adauga_reteta("VitaminaC");
	srv.adauga_reteta("Aspirina");

	srv.delete_medicament("VitaminaC");
	assert(srv.get_all().size() == 1);
	Medicament med = srv.get(0);
	assert(med.get_denumire() == "Aspirina");
	assert(med.get_producator() == "Carl");
	assert(med.get_substanta() == "acid acetilsalicilic");
	assert(med.get_pret() == 15);

	srv.update_medicament("Aspirina", Medicament("Ibusinus", "Laropharm", "ibuprofen", 35));
	med = srv.get(0);
	assert(med.get_denumire() == "Ibusinus");
	assert(med.get_producator() == "Laropharm");
	assert(med.get_substanta() == "ibuprofen");
	assert(med.get_pret() == 35);

	Medicament m = srv.find_medicament("Ibusinus");
	assert(m.get_denumire() == "Ibusinus");

	try {
		srv.find_medicament("Ascovit");
		assert(false);
	}
	catch (const RepoException& ex)
	{
		assert(ex.getMessage() == "Medicamentul nu exista in stoc!\n");
	}

	srv.add_medicament(Medicament("VitaminaC", "Bayer", "acid ascorbic", 22));
	srv.add_medicament(Medicament("Aspirina", "Carl", "acid acetilsalicilic", 15));

	srv.goleste_reteta();
	srv.adauga_reteta("VitaminaC");
	assert(srv.dim_reteta() == 1);
	srv.adauga_reteta("Aspirina");
	srv.genereaza_reteta(3);
	assert(srv.dim_reteta() == 5);
	srv.goleste_reteta();
	assert(srv.dim_reteta() == 0);

	DTO dto;
	assert(dto.get_count() == 0);
	srv.add_medicament(Medicament("aaa", "Carl", "acid", 15));
	const std::map<string, DTO> rez = srv.producator();
	assert(rez.begin()->first == "Bayer");
}

void test_filtrare()
{

	Repository r;
	Validator valid;
	Reteta reteta{ r };
	Service srv{ r, valid , reteta };
	srv.add_medicament(Medicament("VitaminaC", "Bayer", "acid", 22));
	srv.add_medicament(Medicament("Aspirina", "Carl", "vitamina", 22));
	srv.add_medicament(Medicament("Ampicilina", "Laropharm", "acid", 17));
	srv.add_medicament(Medicament("Voltaren", "Carl", "diclofenac", 70));
	srv.add_medicament(Medicament("Parasinus", "Laropharm", "ibuprofen", 30));

	vector<Medicament> rez = srv.filter_subst("acid");
	assert(rez.size() == 2);

	rez = srv.filter_pret(25);
	assert(rez.size() == 3);

}

void test_sortare() {
	
	Repository r;
	Validator valid;
	Reteta reteta{ r };
	Service srv{ r, valid , reteta };

	srv.add_medicament(Medicament("Aspirina", "Carl", "vitamina", 22));
	srv.add_medicament(Medicament("VitaminaC", "Bayer", "acid", 22));
	srv.add_medicament(Medicament("Ampicilina", "Laropharm", "acid", 17));
	srv.add_medicament(Medicament("Voltaren", "Carl", "diclofenac", 70));
	srv.add_medicament(Medicament("Parasinus", "Laropharm", "acid", 12));
	assert(r.get_all().size() == 5);

	vector<Medicament> rez = srv.sort_denumire();
	assert(rez.at(0).get_denumire() == "Ampicilina");

	rez = srv.sort_producator();
	assert(rez.at(0).get_producator() == "Bayer");

	rez = srv.sort_subst_pret();
	assert(rez.at(0).get_denumire() == "Parasinus");
}

void test_validare() {

	Validator valid;
	Medicament med = Medicament("Nurofen", "Reckitt", "Ibuprofen", 32.5);
	valid.validare_med(med);

	try {
		valid.validare_med(Medicament("", "", "", -23));
		assert(false);
	}
	catch (const ValidException& ex)
	{
		assert(ex.getMessage() == "Denumire medicament invalida!\nPret medicament invalid!\nProducator medicament invalid!\nSubstanta medicament invalida!\n");
	}

	try {
		valid.validare_den("");
		assert(false);
	}
	catch (const ValidException& ex)
	{
		assert(ex.getMessage() == "Denumire medicament invalida!\n");
	}

	try {
		valid.validare_subst("");
		assert(false);
	}
	catch (const ValidException& ex)
	{
		assert(ex.getMessage() == "Substanta medicament invalida!\n");
	}
}


void all_tests()
{
	test_domain();
	test_repo();
	test_service();
	test_filtrare();
	test_sortare();
	test_validare();
	
}