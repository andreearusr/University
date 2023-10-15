#pragma once

#include "Abonament.h"
#include<string>
using std::string;

#include<vector>
using std::vector;

class Repository
{

private:
	string fNume;
	vector<Abonament> repo;

public:
	//constructorul implicit
	Repository() = default;

	//nu se mai pot copia obiecte de tip Repository
	Repository(const Repository& ot) = delete;

	// construnctorul Repository-ului
	// fNume - nume de fisier -- string
	Repository(const string& fNume) : fNume{ fNume } 
	{
		loadFromFile();
	};

	//functie pentru incarcarea datelor din fisier
	void loadFromFile();

	//functie pentru adaugarea unui Abonament
	// a- abonamentul de adaugat
	void adauga(const Abonament& a);

	//functie ce returneaza toate Abonamentele din repo
	vector<Abonament>& get_all();
};


