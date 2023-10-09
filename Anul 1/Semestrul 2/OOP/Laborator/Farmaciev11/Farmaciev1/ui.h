#pragma once
#include "service.h"
#include <vector>
using std::vector;


class Consola {

private: 
	Service& srv;

public:
	Consola() = default;
	/*
	functie pentru creeare UI
	date de intrare
		srv - service-ul de medicamente
	post: obiect de tip Consola
	*/
	Consola(Service& srv) noexcept : srv{ srv } {};

	//nu se mai pot copia obiectele de tip Consola
	Consola(const Consola& ot) = delete;

	/*
	functie pentru afisarea listei de medicamente
	date de intrare:
		medicamente - lista de medicamente
	post: medicamentele din lista sunt afisate
	*/
	void print(vector<Medicament>& medicamente) const;

	//functie pentru afisarea meniului
	void meniu() const;

	//functie de rulare UI
	void run();

};