#pragma once

#define NULL_TELEM -1
#define MAX 10
typedef int TElem;

class IteratorMultime;
class Nod;

class Nod {
private:
	TElem e;
	Nod* urm;

public:

	friend class Multime;
	friend class IteratorMultime;

	//Θ(1)
	Nod(TElem e, Nod* urm);
};



class Multime {
	friend class IteratorMultime;

private:
	int n; //nr elemente din multime
	int m; //nr de locatii din TD
	Nod* l[MAX];  //listele independente

	//Θ(1)
	int d(TElem e) const; //functia de dispersie

public:

	//O(m)
	//constructorul implicit
	Multime();

	//O(k)
	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//O(k)
	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//O(k)
	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;

	//Θ(1)
	//intoarce numarul de elemente din multime;
	int dim() const;

	//Θ(1)
	//verifica daca multimea e vida;
	bool vida() const;

	//Θ(1)
	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	//O(m*k)
	// destructorul multimii
	~Multime();


	int diferenta(const Multime& b);
	/*
	Complexitati:
	-caz favorabil= caz mediu = caz defavorabil = Θ(m*m)
	-caz general: Θ(m*m)


	* pre: a,b este o Multime
	* post: Multimea a contine elementele care nu apar in b ( a' = a\b)
	* nr- 
	* returneaza numarul de elemente eliminate
	Subalgoritm diferenta(Multime a, Multime b)
		nr <- 0
		iterator(b,im)
		Pentru i=0,dim(b) executa

			element(im, el)
			Daca cauta(el)==True atunci
				sterge(el)
				nr<-nr+1
			SfDaca
			urmator(im)
		SfPentru
		@returneaza nr

	SfSubalgoritm

	 */
};




