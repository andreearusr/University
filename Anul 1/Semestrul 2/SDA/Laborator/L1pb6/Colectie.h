#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
    int cp; //capacitata
	int n; //nr elemente
	int m; //minim
	int M; //maxim
	TElem* frecv;

	///O(n)
	//void redim();
	void redim(TElem e);

public:

        ///Θ(1)
		//constructorul implicit
		Colectie();

		///O(n)
		//adauga un element in colectie
		void adauga(TElem e);

		///O(n^2)
		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		///Θ(1)
		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		///Θ(1)
		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;


		///Θ(1)
		//intoarce numarul de elemente din colectie;
		int dim() const;

		///Θ(1)
		//verifica daca colectia e vida;
		bool vida() const;

		///Θ(1)
		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		///Θ(1)
		// destructorul colectiei
		~Colectie();




};
