#include "Service.h"
#include"Abonament.h"
#include<algorithm>
#include<iterator>

vector <Abonament>& Service::get_all() {
	return all.get_all();
}

vector<Abonament> Service::sortare()
{
	vector<Abonament> rez = all.get_all();
	std::sort(rez.begin(), rez.end(), [](Abonament& ab1, Abonament& ab2) {
		return ab1.get_numar() > ab2.get_numar();
		});

	return rez;

}