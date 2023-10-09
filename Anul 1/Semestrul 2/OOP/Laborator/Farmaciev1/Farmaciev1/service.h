#pragma once
#include <string>
#include "repo.h"
#include "domain.h"
#include"Reteta.h"
#include "validare.h"
#include "undo.h"

#include <map>
#include <vector>
using std::vector;
using std::string;
using std::unique_ptr;
//typedef bool(*functie) (const Medicament&, const Medicament&);



class DTO {

private:
	string tip;
	int count;

public:
	DTO() : tip{ "" }, count{0}{};
	DTO(string tip) : tip{ tip }, count{ 1 } {};
	string get_prod() {
		return tip;
	}
	void creste() noexcept
	{
		count++;
	}
	int get_count() 
	{
		return count;
	}

};

class Service {

private:
	Repository& all;
	Validator& valid;
	Reteta& reteta;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;

public:

	//constructorul implicit al service-ului
	Service() = default;

	/*
	functie pentru creeare service
	date de intrare
		all - repository-ul de medicamente
		valid - validator
		reteta - reteta de medicamente
	post: obiect de tip Service
	*/
	Service(Repository& all, Validator& valid, Reteta& reteta) noexcept : all{ all }, valid{ valid }, reteta{ reteta } {};

	//nu se mai pot copia obiectele de tip Service
	Service(const Service& ot) = delete;

	/*
	functie pentru adaugarea unui medicament in lista
	date de intrare:
		med - medicamentul ce se doreste a fi adaugat
	post: medicamentul este adaugat in lista
	*/
	void add_medicament(const Medicament& med);

	/*
	functie pentru stergerea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi sters
	post: medicamentul este sters daca el exista lista
	*/
	void delete_medicament(const string& denumire);

	/*
	functie pentru actualizarea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi actualizat
		med - noul medicament
	post: medicamentul vechi este actualizat daca exista in lista
	*/
	void update_medicament(const string& denumire, const Medicament& med);

	/*
	functie pentru cautarea unui medicament in lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi cautat
	post:  se returneaza pozitia medicamentului pe care a fost gasit
		    sau -1 daca nu exista in lista
	*/
	const Medicament& find_medicament(const string& denumire);


	/*
	functie pentru gasirea unui medicament din lista de pe o anumita pozitie
	date de intrare:
		poz - pozitia medicamentului in lista
	post: se returneaza medicamentul

	*/
	Medicament& get(int poz);

	/*
	functie pentru filtrarea medicamentelor dupa substanta activa
	date de intrare:
		substanta - substanta activa a medicamentului - string
	post: se returneaza toate medicamentele din stoc care au ca si substanta activa, substanta
	*/
	vector<Medicament> filter_subst(const string& substanta);

	/*
	functie pentru filtrarea medicamentelor dupa pret
	date de intrare:
		pret - pretul medicamentului - float
	post: se returneaza toate medicamentele din stoc care au un pret mai mic sau egal cu pret
	*/
	vector<Medicament> filter_pret( float pret);


	/*
	functie pentru sortarea medicamentelor dupa denumire
	date de intrare:
		-
	post: se returneaza medicamentele din stoc ordonate crescator dupa denumirea medicamentului
	*/
	vector<Medicament> sort_denumire();

	/*
	functie pentru sortarea medicamentelor dupa producator
	date de intrare:
		-
	post: se returneaza medicamentele din stoc ordonate crescator dupa producatorul medicamentului
	*/
	vector<Medicament> sort_producator();


	/*
	functie pentru sortarea medicamentelor dupa substanta+pret
	date de intrare:
		-
	post: se returneaza medicamentele din stoc ordonate crescator dupa substanta medicamentului,
		iar la substante egale, se sorteaza dupa pret
	*/
	vector<Medicament> sort_subst_pret();

	/*
	functie generica de sortare
	date de intrare:
		*functie - o functie booleana
		referinte spre 2 medicamente
	post: se returneaza medicamentele sortate dupa functia data
	*/
	//vector<Medicament> generalSort(bool(*functie)(Medicament&, Medicament&));


	////functie pentru returnarea tuturor medicamentelor din lista
	vector<Medicament>& get_all() const noexcept;

	/*
	functie pentru adaugare medicament in Reteta
	date de intrare:
		denumire - denumirea medicamentului de adaugat
	post: medicamentul e adaugat in reteta
	*/
	void adauga_reteta(const string& denumire);

	/*
	functie pentru stergere toate medicamentele din Reteta
	date de intrare -
	post: Reteta nu contine niciun medicament
	*/
	void goleste_reteta() noexcept;

	/*
	functie pentru adaugare medicamente random in Reteta
	date de intrare:
		nr - cate medicamente random sa se adauge
	post: in Reteta au fost adaugate nr medicamente random
	*/
	void genereaza_reteta(int nr);

	//functie ce returneaza numarul de medicamente din Reteta
	int dim_reteta() noexcept;


	//functie pentru raport - dupa producator
	std::map<string, DTO> producator();

	/*
	functie pentru export intr-un fisier, medicamentele din Reteta
	date de intrare:
		fisier - numele fisierului in care se exporta
	post: fisier contine medicamentele din Reteta
	*/
	void exporteaza(const string& fisier);

	//functie pentru undo
	void undo();
};
