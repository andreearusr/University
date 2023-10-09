#pragma once

#include "domain.h"
#include "repo.h"

/*
o structura de tip Agentie care cotine: -> o structura de tipul Lista pentru lista de oferte
										-> o structura de tipul lista pentru lista de undo
*/
typedef struct {
	Lista* Oferte;
	Lista* undoList;
}Agentie;

/*
Functie de creare a unei Agentii
Date de intrare: -
Date de iesire: returneaza o Agentie
*/
Agentie* creeazaAgentie();

/*
Functie de distrugere a unei Agentii
Date de intrare: adresa unei Agentii
Date de iesire: memoria este dealocata
*/
void destroyAgentie(Agentie* ag);

// Functia primeste toate detaliile necesare generarii unei oferte, o genereaza, o valideaza si daca aceasta este valida
// si nu mai exista o alta oferta in lista cu aceeasi adresa, se introduce in lista
//	Date de intrare:- ag = adresa unei liste de tip Agentie
//					- tip = string
//					- suprafata = numar real
//					- adresa = string
//					- pret = numar real
// Date iesire:		Daca mai exista atunci se returneaza info cu codul 2
//					Daca parametrii ofertei nu sunt valizi se returneaza info cu codul 1
//					Daca totul a fost in regula se returneaza info cu codul 0
Informatii SRV_adauga(Agentie* ag, char* tip, double suprafata, char* adresa, double pret);


// Functia primeste un id deja valid si modifica oferta de pe pozitia id-1 in vector
//	Date de intrare:- ag = adresa unei liste de tip Agentie
//					- id = un numar natural nenul mai mic decat lungimea listei
//					- tip = string
//					- suprafata = numar real
//					- adresa = string
//					- pret = numar real
//	Date de iesire:	Daca parametrii ofertei nu sunt valizi se returneaza info cu codul 1
//					Daca totul a fost in regula se returneaza info cu codul 0
Informatii SRV_modifica(Agentie* ag, int id, char* tip, double suprafata, char* adresa, double pret);



// Functia sterge o oferta de tip Oferta din repo, de pe pozitia id-1, id-1 fiind o pozitie valida
// Date de intrare:- ag = adresa unei liste de tip Agentie
//				   - id = un numar natural nenul mai mic decat lungimea listei
// Post: lista repo din care a fost sters elementul de pe pozitia id-1
Informatii SRV_stergere(Agentie* ag, int id);


// Functia sorteaza lista de oferte dupa un criteriu dat ca string ("pret"/"tip") si intr-o anumita ordine ("crescator"/"descrescator")
//	Date de intrare:- l = adresa unei liste de tip Lista
//					- criteriu = un string dintre ("pret"/"tip")
//					- ordine = -1 daca de doreste ordonarea descrescatoare
//								0 daca se doreste ordonarea crescatoare
// Post: lista repo a fost ordonata
Informatii SRV_ordonate(Lista* l, char* criteriu, int ordine);

// Functia filtreaza oferte dupa un anumit criteriu ("tip"/"suprafata"/"pret") si le adauga intr-o lista noua pe cele care satisfac criteriul
//		Daca criteriul este "tip" atunci utilizatorul mai trebuie sa introduca dupa ce tip sa se faca filtrarea ("casa"/"teren"/"apartament")
//		Daca criteriul este "suprafata" sau "pret" atunci utilizatorul introduce un numar iar mai apoi cuvantul "maxima"/"minima" pentru a 
//		specifica programului ca numarul dat este valoarea minima/maxima dupa care se doreste sa se faca filtrarea
//			Daca nu se gasesc oferte care sa satisfaca filtrarea se returneaza info cod 1
//	Date de intrare:- l = adresa unei liste de tip Lista
//					- f = adresa unei liste goale de tip Lista in care se vor adauga ofertele care satisfac criteriile
//					- criteriu = un string dintre ("tip"/"suprafata"/"pret")
//					- tip = un string dintre ("casa"/"teren"/"apartament") daca criteriu == "tip" sau un string dintre ("maxima"/"minima") daca criteriu == "suprafata" sau "pret"
//					- nr = un numar real care este luat in considerare cand criteriu == "suprafata" sau "pret"
//	Date de iesire: info code 0 daca a fost macar un astfel de element
//					info code 1 daca nu a existat niciun element
Informatii SRV_filtrare(Lista* l, Lista* f, char* criteriu, char* tip, double nr);


/*
Functie pentru undo pe lista
Date de intrare: adresa unei Agentii
Date de iesire: info code 0 daca se poate face undo
				info code 1 daca nu se mai poate face undo -> "Nu se mai poate face undo!\n" 
*/
Informatii undo(Agentie* ag);

int SRV_cauta(Agentie* ag, int id, int pret);
