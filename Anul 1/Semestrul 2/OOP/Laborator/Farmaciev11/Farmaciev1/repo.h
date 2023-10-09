#pragma once
#include <iostream>
#include "domain.h"
#include <vector>
#include <map>
#include <assert.h>

using std::vector;

class Repo {

public:
	//functie virtuala pentru adaugare medicament
	virtual void add_medicament(const Medicament& med) = 0;

	//functie virtuala pentru stergere medicament
	virtual void delete_medicament(const string& denumire) = 0;

	//functie virtuala pentru cautare medicament
	virtual const Medicament& find(const string& denumire) = 0;

	//functie virtuala pentru gasire medicament de pe o pozitie data
	virtual Medicament& get(int poz) = 0;

	//functie virtuala pentru actualizare medicament
	virtual void update_medicament(const string& denumire, const Medicament& med) = 0;

	//functie virtuala pentru gasire toate medicamente
	virtual vector<Medicament>& get_all() = 0;
};


class RepoException {
	std::string msg;
public:
	/*
	functie pentru creeare RepoException
	date de intrare
		m - mesajul exceptiei - string
	post: obiect de tip RepoException
	*/
	RepoException(const string& m) : msg{ m } {} 

	//functie ce returneaza mesajul exceptiei de tip RepoException ce apare
	string getMessage() const;
};

class Repository: public Repo {

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
	 void add_medicament(const Medicament& med) override;

	/*
	functie pentru stergerea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi sters
	post: medicamentul este sters daca el exista lista
	arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "Medicamentul nu exista in stoc!\n"

	*/
	 void delete_medicament(const string& denumire) override;
	

	/*
	functie pentru cautarea unui medicament in lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi cautat
	post:  se returneaza pozitia medicamentului pe care a fost gasit
		    sau -1 daca nu exista in lista
	*/
	 const Medicament& find(const string& denumire) override;

	/*
	functie pentru gasirea unui medicament din lista de pe o anumita pozitie
	date de intrare:
		poz - pozitia medicamentului in lista
	post: se returneaza medicamentul
	
	*/
	 Medicament& get(int poz) override;

	/*
	functie pentru actualizarea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi actualizat
		med - noul medicament
	post: medicamentul vechi este actualizat daca exista in lista
    arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "Medicamentul nu exista in stoc!\n"
	*/
	 void update_medicament(const string& denumire, const Medicament& med) override;


	//functie pentru returnarea tuturor medicamentelor din lista
	 vector<Medicament>& get_all() override;

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


class RepoLab: public Repo {

private:
	std::map<string, Medicament> repolab;
	vector<Medicament> meds;
	float p;

	/*
	functie pentru generare random numar intre 0 si 1
	*/
	float generare(){
		float random = ((float)rand())/(float)RAND_MAX;
		return random;
	}

public:
	//constructorul implicit al RepoLab-ului
	RepoLab() = default;

	/*
	functie pentru creeare RepoLab
	date de intrare:
		p - un procent - float
	post: obiect de tip RepoLab
	*/
	RepoLab(float p) :p{ p } {}

	//nu se mai pot copia obiectele de tip RepoLab
	RepoLab(const RepoLab& ot) = delete;

	//destructorul RepoLab-ului
	~RepoLab() = default;


	/*
	functie pentru adaugarea unui medicament in lista - metoda Repo suprascrisa
	date de intrare:
		med - medicamentul ce se doreste a fi adaugat
	post: medicamentul este adaugat in lista
	arunca exceptie de tipul RepoException daca procentul random generat este < decat p  "procent"
	arunca exceptie de tipul RepoException daca medicamentul exista deja in stoc => "p"
	*/
	void add_medicament(const Medicament& med) override;


	/*
	functie pentru stergerea unui medicament din lista - metoda Repo suprascrisa
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi sters
	post: medicamentul este sters daca el exista lista
	arunca exceptie de tipul RepoException daca procentul random generat este < decat p  "procent"
	arunca exceptie de tipul RepoException daca medicamentul nu exista in stoc => "p"
	*/
	void delete_medicament(const string& denumire) override;

	/*
	functie pentru cautarea unui medicament in lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi cautat
	post:  se returneaza medicamentul daca a fost gasit
	arunca exceptie de tipul RepoException daca procentul random generat este < decat p  "procent"
	arunca exceptie de tipul RepoException daca medicamentul nu este gasit => "p"
	*/
	const Medicament& find(const string& denumire) override;

	/*
	functie pentru actualizarea unui medicament din lista
	date de intrare:
		denumire - denumirea medicamentului ce se doreste a fi actualizat
		med - noul medicament
	post: medicamentul vechi este actualizat daca exista in lista
	arunca exceptie de tipul RepoException daca procentul random generat este < decat p  "procent"
	arunca exceptie de tipul RepoException daca medicamentul nu este gasit => "p"
	*/
	void update_medicament(const string& denumire, const Medicament& med) override;

	//functie pentru returnarea tuturor medicamentelor din lista
	vector<Medicament>& get_all() override;

	/*
	functie pentru gasirea unui medicament din lista de pe o anumita pozitie
	date de intrare:
		poz - pozitia medicamentului in lista
	post: se returneaza medicamentul
	arunca exceptie de tipul RepoException daca procentul random generat este < decat p  "procent"
	*/
	Medicament& get(int poz) override;
};