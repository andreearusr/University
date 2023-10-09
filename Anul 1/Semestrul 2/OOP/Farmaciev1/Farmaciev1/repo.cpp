
#include "repo.h"
#include <assert.h>
#include "domain.h"
#include <algorithm>
#include <iterator>


string RepoException::getMessage() const{
	return msg; 
}

void Repository::add_medicament(const Medicament& med) {
	for(const auto& m: repo)
		if (m.get_denumire() == med.get_denumire()) {
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
		throw RepoException("Medicamentul nu exista in stoc!\n");}

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

	vector<Medicament>::iterator i = std::find_if(repo.begin(), repo.end(), [denumire](const Medicament& med) {
		return med.get_denumire() == denumire;
		});
	if (i == repo.end())
		throw RepoException("Medicamentul nu exista in stoc!\n");
	else
		return *i;}


Medicament& Repository::get(int poz) {
	return repo.at(poz);
}


vector<Medicament>& Repository::get_all() noexcept{
	return repo;
}





