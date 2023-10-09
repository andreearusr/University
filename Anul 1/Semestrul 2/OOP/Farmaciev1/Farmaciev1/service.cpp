
#include <iostream>
#include "service.h"
#include <assert.h>
#include <iterator>
#include <algorithm>
#include <string>

void Service::add_medicament(const Medicament& med)
{
	valid.validare_med(med);
	all.add_medicament(med);
}

void Service::delete_medicament(const string& denumire) {
	valid.validare_den(denumire);
	reteta.sterge(denumire);
	all.delete_medicament(denumire);
	
}


vector<Medicament>& Service::get_all() const noexcept {
	return all.get_all();
}

void Service::update_medicament(const string& denumire, const Medicament& med) {
	
	valid.validare_med(med);
	valid.validare_den(denumire);
	reteta.modifica(denumire, med);
	all.update_medicament(denumire, med);
	
}

const Medicament& Service::find_medicament(const string& denumire) {
	valid.validare_den(denumire);
	return all.find(denumire);
}

Medicament& Service::get(int poz)
{
	return all.get(poz);
}


vector<Medicament> Service::filter_pret(float pret) {
	vector<Medicament> rez;
	std::copy_if(all.get_all().begin(), all.get_all().end(), std::back_inserter(rez),
		[pret](const Medicament& med) noexcept {return med.get_pret() <= pret; });
	return rez;

	/*vector<Medicament> rez;
	for (auto& med : all.get_all())
		if (med.get_pret() <= pret)
			rez.push_back(med);*/
	
}


vector<Medicament> Service::filter_subst(const string& substanta){
	vector<Medicament> rez;
	std::copy_if(all.get_all().begin(), all.get_all().end(), std::back_inserter(rez),
		[substanta](const Medicament& med) {return med.get_substanta() == substanta; });
	return rez;

	/*valid.validare_subst(substanta);
	vector<Medicament> rez;
	for (auto& med : all.get_all())
		if (med.get_substanta() == substanta)
			rez.push_back(med);
	*/
}


/*
vector<Medicament> Service::generalSort(bool (*functie)(Medicament&, Medicament&)){
	
	vector<Medicament> r{ all.get_all() };//fac o copie
	if (*functie != nullptr)
	{
	for (int i = 0; i < r.size()-1; i++) {
		for (int j = i + 1; j < r.size(); j++) {
			//if (functie(r.get(i), r.get(j)) == false)
				{
				//std::swap(r.get(i), r.get(j));
				//Medicament aux = r.get(i);
				//r.get(i) = r.get(j);
				//r.get(j) = aux;
				}
			}
		}
	}
	return r;
	
}
*/

vector<Medicament> Service::sort_denumire() 
{
	vector<Medicament> rez = all.get_all();;
	std::sort(rez.begin(), rez.end(), [](Medicament& m1, Medicament& m2) 
		{return m1.get_denumire() < m2.get_denumire();
		});
	return rez;

	/*return generalSort([]( Medicament& m1,  Medicament& m2) {
		return m1.get_denumire() < m2.get_denumire();
		});*/
}

vector<Medicament> Service::sort_producator()
{
	vector<Medicament> rez = all.get_all();;
	std::sort(rez.begin(), rez.end(), [](Medicament& m1, Medicament& m2)
		{return m1.get_producator() < m2.get_producator();
		});
	return rez;


	/*return generalSort([](Medicament& m1, Medicament& m2) {
		return m1.get_producator() < m2.get_producator();
		});*/
}

vector<Medicament> Service::sort_subst_pret()
{
	vector<Medicament> rez = all.get_all();;
	std::sort(rez.begin(), rez.end(), [](Medicament& m1, Medicament& m2)
		{return (m1.get_substanta() < m2.get_substanta()) || (m1.get_substanta() == m2.get_substanta() && m1.get_pret() < m2.get_pret());
		});
	return rez;

	/*return generalSort([](Medicament& m1, Medicament& m2) {
		return (m1.get_substanta() < m2.get_substanta()) || (m1.get_substanta() == m2.get_substanta() && m1.get_pret() < m2.get_pret());
		});*/
}


void Service::adauga_reteta(const string& denumire) {
	valid.validare_den(denumire);
	reteta.adauga(denumire);
}

void Service::goleste_reteta() noexcept {
	reteta.goleste();
}

void Service::genereaza_reteta(int nr) {
	reteta.genereaza(nr);
}

int Service::dim_reteta() noexcept {
	return reteta.dimensiune();
}


std::map<string, DTO> Service::producator()
{
	std::map<string, DTO> rez;
	for (const auto& med : all.get_all())
	{
		if (rez.find( med.get_producator()) == rez.end())
		{
			rez[med.get_producator()] = DTO(med.get_producator());
		}
		else
		{
			rez[med.get_producator()].creste();
		}
	}
	return rez;
}
