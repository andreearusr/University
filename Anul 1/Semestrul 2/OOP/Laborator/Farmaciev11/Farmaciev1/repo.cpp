
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


vector<Medicament>& Repository::get_all(){
	return repo;
}



void RepoFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) {
		throw RepoException("Nu putem deschide fisierul:" + fName);
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

void RepoLab::add_medicament(const Medicament& med)
{
	float prob = generare();
	if (prob < p)
		throw RepoException(std::to_string(prob));

	for (const auto& m : repolab)
	{
		if (m.first == med.get_denumire())
			throw RepoException(std::to_string(p));
	}

	repolab[med.get_denumire()] = med;
}

void RepoLab::delete_medicament(const string& denumire) 
{
	float prob = generare();
	if (prob < p)
		throw RepoException(std::to_string(prob));

	int ok = 1;
	for (const auto& m : repolab)
	{
		if (m.first == denumire) {
			repolab.erase(m.first);
			ok = 0;
			return;
		}
	}
	if(ok==1)
		throw RepoException(std::to_string(p));

}

const Medicament& RepoLab::find(const string& denumire) 
{
	float prob = generare();
	if (prob < p)
		throw RepoException(std::to_string(prob));

	for (const auto& m : repolab)
	{
		if (m.first == denumire)
			return m.second;
	}
	throw RepoException(std::to_string(p));
}



void RepoLab::update_medicament(const string& denumire, const Medicament& med) 
{
	float prob = generare();
	if (prob < p)
		throw RepoException(std::to_string(prob));
	int ok = 1;
	for (const auto& m : repolab)
	{
		if (m.first == denumire)
		{
			//repolab[denumire] = med;
			repolab.erase(m.first);
			repolab[med.get_denumire()] = med;
			ok = 0;
			return;
		}
	}
	if(ok==1)
		throw RepoException(std::to_string(p));
}

vector<Medicament>& RepoLab::get_all() 
{
	meds.clear();
	for (const auto& m : repolab)
	{
		meds.push_back(m.second);
	}

	return meds;
}

Medicament& RepoLab::get(int poz) 
{
	float prob = generare();
	if (prob < p)
		throw RepoException(std::to_string(prob));
	return meds.at(poz);
}