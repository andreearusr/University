#include "Repository.h"
#include <fstream>

void Repository::adauga(const Abonament& a)
{
	repo.push_back(a);
}

void Repository::loadFromFile() {

	std::ifstream in(fNume);
	

	while (!in.eof())
	{
		string numeAbonat;
		string tip;
		int pretIntrare;
		int numarIntrari;

		in >> numeAbonat;
		in >> tip;
		in >> pretIntrare;
		if (in.eof())
		{
			break;
		}
		in >> numarIntrari;
		if (in.eof())
		{
			break;
		}

		Abonament a{ numeAbonat, tip, pretIntrare, numarIntrari };
		adauga(a);
	}
	in.close();
}


vector<Abonament>& Repository::get_all() {
	return repo;
}