#pragma once
#include "repo.h"
#include "domain.h"

#include <string>
#include <iostream>
#include <vector>
using std::string;
using std::vector;

class Reteta
{
private:
	vector<Medicament> inReteta;
	Repository& repo;
	int n; 

public:
	//constructorul implicit al retetei
	Reteta() = default;

	/*
	functie pentru creeare reteta
	date de intrare
		repo - repository-ul de medicamente
	post: obiect de tip Reteta
	*/
	Reteta(Repository& repo) noexcept : repo{ repo } {} ;

	//nu se mai pot copia obiectele de tip Reteta
	//Reteta(const Reteta& reteta) = delete;


	/*
	functie pentru adaugare medicament in Reteta
	date de intrare:
		denumire - denumirea medicamentului de adaugat
	post: medicamentul e adaugat in reteta
	*/
	void adauga(const string& denumire);

	/*
	functie pentru stergere toate medicamentele din Reteta
	date de intrare -
	post: Reteta nu contine niciun medicament
	*/
	void goleste() noexcept;

	/*
	functie pentru adaugare medicamente random in Reteta
	date de intrare:
		nr - cate medicamente random sa se adauge
	post: in Reteta au fost adaugate nr medicamente random
	*/
	void genereaza(int nr);

	// functie ce returneaza numarul de medicamente din Reteta
	int dimensiune() noexcept;

	void sterge(const string& den);
	void modifica(const string& den, const Medicament& med);


};

