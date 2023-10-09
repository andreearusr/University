#pragma once
#include "domain.h"
using std::string;


class ValidException {
	string msg;
public:

	/*
	functie pentru creeare ValidException
	date de intrare
		m - mesajul exceptiei - string
	post: obiect de tip ValidException
	*/
	ValidException(const string& m) : msg{ m } {}

	//functie ce returneaza mesajul exceptiei de tip ValidException ce apare
	string getMessage() const;
};


class Validator {

public:
	//constructorul implicit al validatorului
	Validator() = default;

	//nu se mai pot copia obiectele de tip Validaor
	Validator(const Validator& validator) = delete;

	/*
	functie pentru validarea unui medicament
	date de intrare:
		med - medicamentul ce se doreste a fi validat
	post: medicamentul e validat
	arunca exceptie de tipul ValidException daca medicamentul :
			denumire == ""  -> "Denumire medicament invalida!\n"
			producator == ""  -> "Producator medicament invalid!\n"
			substanta activa ==""  -> "Substanta medicament invalida!\n
			pret<0  -> "Pret medicament invalid!\n"
	*/
	void validare_med(const Medicament& med);

	/*
	functie pentru validarea denumirii unui medicament
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi validata
	post: denumirea e validata
	arunca exceptie de tipul ValidException daca denumire == ""  -> "Denumire medicament invalida!\n" 
	*/
	void validare_den(const string& denumire);

	/*
	functie pentru validarea substantei unui medicament
	date de intrare:
		substanta - substanta activa a medicamentului ce se doreste a fi validata
	post: substanta e validata
	arunca exceptie de tipul ValidException daca substanta == ""  -> "Substanta medicament invalida!\n"
	*/
	void validare_subst(const string& substanta);

};

