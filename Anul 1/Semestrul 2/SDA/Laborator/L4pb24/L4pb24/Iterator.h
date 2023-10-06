#pragma once

#include "LO.h"

class Iterator {
	friend class LO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	const LO& lo;

	int curent;

public:

	//Θ(1)
	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//Θ(1)
	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//Θ(1)
	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//Θ(1)
	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElement element() const;



	void revinoKPasi(int k);
    /*
    Complexitati:
    -caz favorabil= caz mediu = caz defavorabil = Θ(k)
    -caz general: Θ(k)
 
    */
 
    /*
    * pre: k este numar intreg, lo este lista ordonata
    * post: iteratorul refera a k-a pereche din urma, din lista ordonata
    Subalgoritm revinoKPasi(LO lo, int k)
        Daca k<=0 atunci
            @arunca exceptie
        SfDaca
 
         Pentru i=0,k executa
            
			curent<-lo.prec->curent
            Daca valid == false atunci
                @arunca exceptie
        SfPentru
    SfSubalgoritm
	 
     */
};


