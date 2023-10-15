#pragma once
#include "Repository.h"
#include"Abonament.h"

class Service
{
private:
	Repository& all;

public:
	//constructorul implicit
	Service() = default;

	//nu se mai pot copia obiecte de tip Service
	Service(const Service& ot) = delete;


	// construnctorul Service-ului
	// all - vectorul de Abonamente
	Service(Repository& all) : all{ all } {};


	//functie ce returneaza toate Abonamentele
	vector <Abonament>& get_all();

	//functie pentru sortarea descrescatoare a abonamentelor
	vector<Abonament> sortare();

};

