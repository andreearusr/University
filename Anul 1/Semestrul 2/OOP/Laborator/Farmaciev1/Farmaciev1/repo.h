#pragma once
#include <iostream>
#include "domain.h"
#include <vector>
#include <map>
#include <assert.h>

using std::vector;


class RepoException {
	std::string msg;
public:
	/*
	functie pentru creeare RepoException
	date de intrare
		m - mesajul exceptiei - string
	post: obiect de tip RepoException
	*/
	RepoException(const string& m) : msg{ m } {} ;

	//functie ce returneaza mesajul exceptiei de tip RepoException ce apare
	string getMessage() const;
};


class Repository {

private:
	vector<Medicament> repo;

public:

	//constructorul implicit al repository-ului
	 Repository() = default;

	//constructorul implicit al repository-ului
	//Repository(const Repository& r);

	//nu se mai pot copia obiectele de tip Repository
	Repository(const Repository& ot) = delete;

	//destructorul Repository-ului
	 ~Repository() = default;

	/*
	functie pentru adaugarea unui medicament in lista
	date de intrare:
		med - medicamentul ce se doreste a fi adaugat
	post: medicamentul este adaugat in lista
	arunca exceptie de tipul RepoException daca medicamentul exista deja in stoc => "Medicamentul exista deja in stoc!\n"
	*/
	 virtual void add_medicament(const Medicament& med) ;

	/*
	functie pentru stergerea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi sters
	post: medicamentul este sters daca el exista lista
	arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "Medicamentul nu exista in stoc!\n"

	*/
	 virtual void delete_medicament(const string& denumire) ;
	

	/*
	functie pentru cautarea unui medicament in lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi cautat
	post:  se returneaza pozitia medicamentului pe care a fost gasit
		    sau -1 daca nu exista in lista
	*/
	 const Medicament& find(const string& denumire) ;

	/*
	functie pentru gasirea unui medicament din lista de pe o anumita pozitie
	date de intrare:
		poz - pozitia medicamentului in lista
	post: se returneaza medicamentul
	
	*/
	 Medicament& get(int poz) ;

	/*
	functie pentru actualizarea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi actualizat
		med - noul medicament
	post: medicamentul vechi este actualizat daca exista in lista
    arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "Medicamentul nu exista in stoc!\n"
	*/
	 virtual void update_medicament(const string& denumire, const Medicament& med) ;


	//functie pentru returnarea tuturor medicamentelor din lista
	 vector<Medicament>& get_all() noexcept;

};


class RepoFile :public Repository {

private:
	string fName;

	//functie pentru incarcarea datelor din fisier
	void loadFromFile();

	//functie pentru scrierea datelor in fisier
	void writeToFile();

public:

	/*
	constructorul RepoFile-ului
	fName - numele fisierului de unde se incarca datele - string
	*/
	RepoFile(string fName) : Repository(), fName{ fName } {
		loadFromFile();
	}


	/*
	functie pentru adaugarea unui medicament in lista - metoda Repository suprascrisa
	date de intrare:
		med - medicamentul ce se doreste a fi adaugat
	post: medicamentul este adaugat in lista
	arunca exceptie de tipul RepoException daca medicamentul exista deja in stoc => "Medicamentul exista deja in stoc!\n"
	*/
	void add_medicament(const Medicament& med) override {
		Repository::add_medicament(med);
		writeToFile();
	}

	/*
	functie pentru stergerea unui medicament din lista - metoda Repository suprascrisa
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi sters
	post: medicamentul este sters daca el exista lista
	arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "Medicamentul nu exista in stoc!\n"

	*/
	void delete_medicament(const string& denumire) override {
		Repository::delete_medicament(denumire);
		writeToFile();
	}

	/*
	functie pentru actualizarea unui medicament din lista - metoda Repository suprascrisa
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi actualizat
		med - noul medicament
	post: medicamentul vechi este actualizat daca exista in lista
	arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "Medicamentul nu exista in stoc!\n"
	*/
	void update_medicament(const string& denumire, const Medicament& med) override {
		Repository::update_medicament(denumire, med);
		writeToFile();
	}

};
