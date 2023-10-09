
#include "repo.h"
#include <assert.h>
#include "domain.h"
#include <algorithm>
#include <iterator>
#include <fstream>


string RepoException::getMessage() const{
	return msg; 
}

void Repository::add_medicament(const Medicament& med) {
	/*for(const auto& m: repo)
		if (m.get_denumire() == med.get_denumire()) {
			throw RepoException("Medicamentul exista deja in stoc!\n");
		}
	repo.push_back(med);*/


	auto found = std::find_if(repo.begin(), repo.end(), [med](const Medicament& m) {
		return m.get_denumire() == med.get_denumire();
		});
	if (found != repo.end()) {
		throw RepoException("Medicamentul exista deja in stoc!\n");
	}
	repo.push_back(med);
}

void Repository::delete_medicament(const string& denumire) {

	int ok = 1;
	int poz = 0;
	for (auto& m : repo)
	{
		if (m.get_denumire() == denumire)
		{
			repo.erase(repo.begin() + poz);
			ok = 0;
		}
		poz++;
	}
	if (ok == 1)
		throw RepoException("Medicamentul nu exista in stoc!\n");

}

void Repository::update_medicament(const string& denumire, const Medicament& med) {
	
	int ok = 1;
	for (auto& m : repo)
	{
		if (m.get_denumire() == denumire)
		{
			m = med;
			ok = 0;
		}
	}
	if(ok==1)
		throw RepoException("Medicamentul nu exista in stoc!\n");
}


const Medicament& Repository::find(const string& denumire) {

	//for (auto& m : repo)
	//{
	//	if (m.get_denumire() == denumire)
	//		return m;
	//}
	//throw RepoException("Medicamentul nu exista in stoc!\n");

	auto found = std::find_if(repo.begin(), repo.end(), [denumire](const Medicament& med) {
		return med.get_denumire() == denumire;
		});
	if (found == repo.end())
		throw RepoException("Medicamentul nu exista in stoc!\n");
	
	return *found;
}


Medicament& Repository::get(int poz) {
	return repo.at(poz);
}


vector<Medicament>& Repository::get_all() noexcept{
	return repo;
}



void RepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) {
		throw RepoException("Nu putem deschide fisierul:" );
	}

	while (!in.eof())
	{
		string denumire, producator, substanta;
		float pret;
		in >> denumire;
		in >> pret;
		if (in.eof())
		{
			break;
		}
		in >> producator;
		in >> substanta;

		Medicament med{ denumire, producator, substanta, pret };
		Repository::add_medicament(med);
	}
	in.close();
}

void RepoFile::writeToFile() {

	std::ofstream out(fName);
	if (!out.is_open()) {
		throw RepoException("Nu putem deschide fisierul:" + fName);
	}

	for (auto& med : get_all())
	{
		out << med.get_denumire() << "\n";
		out << med.get_pret() << "\n";
		out << med.get_producator() << "\n";
		out << med.get_substanta() << "\n";
	}

	out.close();
}

