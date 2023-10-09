
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
	catch (const RepoException&)
	{
		//assert(ex.getMessage() == "Medicamentul nu exista in stoc!\n");
		assert(true);
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

void test_repo_file()
{

	RepoFile r{ "teste.txt" };
	Validator valid;
	Reteta reteta{ r };
	Service srv{ r, valid , reteta };

	r.add_medicament(Medicament("VitaminaC", "Bayer", "acid ascorbic", 22));
	r.add_medicament(Medicament("Aspirina", "Carl", "acid acetilsalicilic", 15));
	assert(r.get_all().size() == 3);
	r.update_medicament("Aspirina", Medicament("Ibusinus", "Laropharm", "ibuprofen", 35));
	r.delete_medicament("VitaminaC");
	r.delete_medicament("Ibusinus");

	try {
		RepoFile rr{ "a.txt" };
		rr.add_medicament(Medicament("a", "a", "a", 11));
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	vector<Medicament> rez = srv.filter_subst("acid");

}
void test_service() {

	Repository r;
	Validator valid;
	Reteta reteta{ r };
	Service srv{ r, valid , reteta};
	srv.add_medicament(Medicament("VitaminaC", "Bayer", "acid ascorbic", 22));
	srv.undo();
	assert(srv.get_all().size() == 0);
	try {
		srv.undo();
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	srv.add_medicament(Medicament("VitaminaC", "Bayer", "acid ascorbic", 22));
	srv.add_medicament(Medicament("Aspirina", "Carl", "acid acetilsalicilic", 15));
	assert(srv.get_all().size() == 2);
	

	srv.adauga_reteta("VitaminaC");
	srv.adauga_reteta("Aspirina");
	srv.exporteaza("ret.txt");

	srv.delete_medicament("VitaminaC");
	srv.undo();
	assert(srv.get_all().size() == 2);
	srv.delete_medicament("VitaminaC");
	assert(srv.get_all().size() == 1);
	Medicament med = srv.get(0);
	assert(med.get_denumire() == "Aspirina");
	assert(med.get_producator() == "Carl");
	assert(med.get_substanta() == "acid acetilsalicilic");
	assert(med.get_pret() == 15);

	srv.update_medicament("Aspirina", Medicament("Ibusinus", "Laropharm", "ibuprofen", 35));
	srv.undo();
	med = srv.get(0);
	assert(med.get_denumire() == "Aspirina");

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
	catch (const RepoException& )
	{
		//assert(ex.getMessage() == "Medicamentul nu exista in stoc!\n");
		assert(true);
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

void test_repo_lab()
{
	RepoLab repo{ 0 };
	// add + get_all
	//try {
			assert(repo.get_all().size() == 0);
			repo.add_medicament(Medicament("Nurofen", "Bayer", "acid", 15));
			assert(repo.get_all().size() == 1);
			try {
				repo.add_medicament(Medicament("Nurofen", "aa", "aa", 15));
				assert(false);
			}
			catch (RepoException& ex) {
				assert(ex.getMessage() == "0.000000");

			}
			repo.add_medicament(Medicament("Parasinus", "Moderna", "paracetamol", 23));
			vector<Medicament>& lista = repo.get_all();
			assert(lista[0].get_denumire() == "Nurofen");
			assert(lista[1].get_denumire() == "Parasinus");

			 //find
			Medicament med = repo.find("Parasinus");
			assert(med.get_denumire() == "Parasinus");
			assert(med.get_producator() == "Moderna");
			assert(med.get_substanta() == "paracetamol");
			assert(med.get_pret() == 23);
			try {
				repo.find("fp");
				assert(false);
			}
			catch (RepoException& ex) {
				assert(ex.getMessage() == "0.000000");
				
			}

			// update
			repo.update_medicament("Nurofen", Medicament("Ibusinus", "Laropharm", "ibuprofen", 35));
			vector<Medicament>& lista2 = repo.get_all();
			assert(lista2[0].get_denumire() == "Ibusinus");
			try {
				repo.update_medicament("VitaminaC", Medicament("aa", "aa", "bb", 35));
				assert(false);
			}
			catch (RepoException& ex) {
				assert(ex.getMessage() == "0.000000");

			}

			// delete
			assert(repo.get_all().size() == 2);
			repo.delete_medicament("Parasinus");
			assert(repo.get_all().size() == 1);
			try {
				repo.delete_medicament("aa");
				assert(false);
			}
			catch (RepoException& ex) {
				assert(ex.getMessage() == "0.000000");

			}

			Medicament m1 = repo.get(0);
		}

		//catch (RepoException& ) {
			//assert(ex.getMessage() < "0" || ex.getMessage() == "0");
		//	assert(true);

		//}
//}

void test_repo_lab1()
{
	RepoLab repo{ 1 };
	vector<Medicament> lista = repo.get_all();

	try {
		repo.add_medicament(Medicament("Nurofen", "aa", "aa", 15));
		assert(false);
	}
	catch (RepoException& ) {
		assert(true);
	}


	try {
		repo.find("fp");
		assert(false);
	}
	catch (RepoException& ) {
		assert(true);
	}

	try {
		repo.update_medicament("VitaminaC", Medicament("aa", "aa", "bb", 35));
		assert(false);
	}
	catch (RepoException& ) {
		assert(true);
	}

	try {
		repo.delete_medicament("aa");
		assert(false);
	}
	catch (RepoException& ) {
		assert(true);
	}

	try {
		Medicament m1 = repo.get(5);
		assert(false);
	}
	catch (RepoException& ) {
		assert(true);

	}

}

void all_tests()
{
	test_domain();
	test_repo();
	test_repo_file();
	test_service();
	test_filtrare();
	test_sortare();
	test_validare();
	test_repo_lab();
	test_repo_lab1();
}