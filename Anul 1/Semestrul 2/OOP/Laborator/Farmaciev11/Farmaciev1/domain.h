#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;

class Medicament {

private:
	string denumire;
	string producator;
	string substanta;
	float pret;

public:

	/*
	functie pentru creearea unui medicament
	date de intrare:
		den - denumirea medicamentului - string
		prod - producatorul medicamentului - string
		subst - substanta activa a medicamentului - string
		pret - pretul medicamentului - float
	date de iesire: obiect de tip medicament
	*/
	Medicament(const string& den, const string& prod, const string& subst, float pret):
		denumire{ den },
		producator{ prod },
		substanta{ subst },
		pret{ pret } {};

	//constructorul implicit al domeniului
	Medicament() = default;

	//constructorul de copiere pentru un medicament
	// date de intrare: ot- un medicament
	//post: obiect de tip medicament
	Medicament(const Medicament& ot) :
		denumire{ ot.denumire },
		producator{ ot.producator },
		substanta{ ot.substanta },
		pret{ ot.pret } {
		std::cout << "Copy constructor called "; };

	//functie ce returneaza denumirea unui medicament
	string get_denumire() const ;

	//functie ce returneaza producatorul unui medicament
	string get_producator() const;

	//functie ce returneaza substanta activa a unui medicament
	string get_substanta() const;

	//functie ce returneaza pretul unui medicament
	float get_pret() const noexcept;

};

