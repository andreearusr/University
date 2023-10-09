#ifndef DOMAIN_H_
#define DOMAIN_H_

// Tip de date care stocheaza:
//	tip - string
//	suprafata - numar real
// 	adresa - string
//	pret - numar real
typedef struct
{
	char* tip;
	double suprafata;
	char* adresa;
	double pret;
}Oferta;

// Tip de date care stocheaza:
//	cod - un numar intreg care simbolizeaza codul de eroare
//		= 0, daca totul este in regula
//		= 1, daca a existat o eroare
//	text - un string care are ca si continut un mesaj despre eroare
typedef struct
{
	char text[100];
	int cod;
}Informatii;

// Functia primeste ca parametrii 2 stringuri, pentru care se aloca memorie dinamica si 2 numere reale pe care le incapsuleaza intr-un struct de tip Oferta
//	Date de intrare:- tip = string
//					- suprafata = numar real
//					- adresa = string
//					- pret = numar real
// Date de iesire: - oferta de tip Oferta
Oferta* createOferta(char* tip, double suprafata, char* adresa, double pret);

// Functia returneaza o copie a unei oferte
// Date intrare: adresa unei oferte
// Date de iesire: o copie a ofertei (out-of-place)
Oferta* copyOferta(Oferta* o);

// Functia distruge o oferta (dealoca memoria)
// Date intrare: adresa unei oferte
// Post: se dealoca memoria ofertei din input
void destroyOferta(Oferta* o);

/*
Functie care returneaza adresa unei oferte
Date de intrare: adresa unei Oferte 
Date de iesire: adresa Ofertei - string
*/
char* get_adr(Oferta* o);

/*
Functie care returneaza tipul unei oferte
Date de intrare: adresa unei Oferte
Date de iesire: tipul Ofertei - string
*/
char* get_tip(Oferta* o);

/*
Functie care returneaza suprafata unei oferte
Date de intrare: adresa unei Oferte
Date de iesire: suprafata Ofertei - intreg
*/
double get_suprafata(Oferta* o);

/*
Functie care returneaza pretul unei oferte
Date de intrare: adresa unei Oferte
Date de iesire: pretul Ofertei - intreg
*/
double get_pret(Oferta* o);
#endif