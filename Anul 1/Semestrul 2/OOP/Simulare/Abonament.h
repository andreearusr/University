#pragma once

#include <string>
using std::string;


class Abonament
{
private:
	string numeAbonat;
	string tip;
	int pretIntrare;
	int numarIntrari;

public:
	//constructorul implicit
	Abonament() = default;

	//functie pentru creeare abonament
	// numeAbonat - nume -- string
	// tip - tip -- string
	// pretIntrare - pret -- intreg
	// numarIntrari - nume -- intreg
	Abonament(const string& numeAbonat, const string& tip, int pretIntrare, int numarIntrari) :
		numeAbonat{ numeAbonat },
		tip{ tip },
		pretIntrare{ pretIntrare },
		numarIntrari{ numarIntrari } {};

	//constructorul de copiere al unui Abonament
	// ot - un abonament
	Abonament(const Abonament& ot) :
		numeAbonat{ ot.numeAbonat },
		tip{ ot.tip },
		pretIntrare{ ot.pretIntrare },
		numarIntrari{ ot.numarIntrari } {};

	//functie ce retunrneaza numele unui abonament
	string get_nume() const;

	//functie ce retunrneaza tipul unui abonament
	string get_tip() const;

	//functie ce retunrneaza pret intrare abonament
	int get_pret() const;

	//functie ce retunrneaza numar intrari abonament
	int get_numar() const;


};

