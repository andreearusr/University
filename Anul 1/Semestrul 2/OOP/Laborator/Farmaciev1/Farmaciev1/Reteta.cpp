#include "Reteta.h"
#include <algorithm>
#include <random> 
#include <chrono>
#include <fstream>

void Reteta::adauga(const string& denumire) {
	inReteta.push_back(repo.find(denumire));
	this->n++;
}

void Reteta::goleste() noexcept {
	inReteta.clear();
	this->n = 0;
}

void Reteta::genereaza(int nr) {
	vector<Medicament> rez = repo.get_all();

	auto const seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(rez.begin(), rez.end(), std::default_random_engine(seed));

	this->n += nr;
	for (auto& m : rez)
	{
		if (nr != 0)
		{
			inReteta.push_back(m);
			nr--;
		}
		//else
			//return;
	}
}

int Reteta::dimensiune() noexcept{
	return this->n;
}

void Reteta::sterge(const string& den) {

	int ok = 1;
	int poz = 0;
	for (auto& m : inReteta)
	{
		if (m.get_denumire() == den)
		{
			inReteta.erase(inReteta.begin() + poz);
			ok = 0;
		}
		poz++;
	}
}

void Reteta::modifica(const string& den, const Medicament& med)
{
	int ok = 1;
	for (auto& m : inReteta)
	{
		if (m.get_denumire() == den)
		{
			m = med;
			ok = 0;
		}
	}
}

void Reteta::export_reteta(const string& fisier)
{
	std::ofstream file(fisier);
	for (auto& m : inReteta)
	{
		file << "Denumire:"<<m.get_denumire()<<",";
		file << "Pret:"<<m.get_pret()<<",";
		file << "Producator:"<<m.get_producator()<<",";
		file << "Substanta:"<<m.get_substanta()<<",";
		file << "\n";
	}
	file.close();
}