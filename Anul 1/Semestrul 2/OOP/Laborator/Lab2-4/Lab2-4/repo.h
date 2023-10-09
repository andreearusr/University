#pragma once
#include "domain.h"


typedef void* ElemType;
/*
Tip de functie pentru distrugerea unei structuri
*/
typedef void(*DestroyFunction)(ElemType);

/*
Tip de functie pentru copierea unui element
*/
typedef void*(*CopyFunction)(ElemType);

// Tip de date care stocheaza o lista de oferte
// ElemType* elems - vector dinamic
//	lg - lungimea vectorului
//	cap - capacitatea vectorului
typedef struct
{
	ElemType* elems;
	int lg;
	int cap;
} Lista;

// Functia returneaza o lista goala, care are capacitatea pentru 2 ElemType initial
// Date intrare: -
// Date iesire: o lista goala, care are capacitatea pentru 2 ElemType initial
Lista* createLista();

// Functia copiaza o lista data
// Date intrare: adresa unei liste, o functie de copiere
// Date de iesire : o copie a listei(out-of-place)
Lista* copyLista(Lista* l, CopyFunction copyF);

// Functia distruge o lista existentat (dealoca memoria)
// Date intrare: adresa unei liste, o functie de distrugere
// Post: se dealoca memoria listei din input
void destroyLista(Lista* l, DestroyFunction destrF);

/*
Functie de distrugere a unei liste
Date intrare: adresa unei liste
Post: se dealoca memoria listei din input
*/
void destroyListaOferte(Lista* l);

/*
Functie de distrugere a ultimului element din lista
Date de intrare: adresa unei liste
Post: lista fara ultimul element
*/
Lista* destroyUltim(Lista* l);


// Functia returneaza un ElemType dintr-o lista, de pe pozitia poz
// Date intrare:- adresa unei liste l de tip Lista
//				- poz = un numar pozitiv mai mic decat lungimea listei l
// Date iesire: un ElemType de pe pozitia poz
ElemType get(Lista* l, int poz);

// Functia modifica un ElemType de pe pozitia poz cu elem_nou
// l - o lista de tip Lista
// poz = un numar pozitiv mai mic decat lungimea listei l
// elem_nou = un ElemType
// Date iesire: ElemType-ul modificat
ElemType set(Lista* l, int poz, ElemType elem_nou);


// Functia returneaza lungimea unei liste
// Date intrare: adresa unei liste de tip Lista
// Date iesire: numar natural - dimesiunea listei l
int size(Lista* l);

// Functia adauga un ElemType intr-o lista
// Date intrare:- adresa unei liste de tip Lista
//				- el - un element de tip ElemType
// Post: se adauga la sfarsitul listei el
void add(Lista* l, ElemType el);

// Functia sterge un ElemType de pe o pozitie data, poz, dintr-o lista
// Date intrare:- adresa unei liste de tip Lista
//				- poz = un numar pozitiv mai mic decat lungimea listei l
// Post: se sterge un ElemType de pe pozitia poz
void del(Lista* l, int poz);
