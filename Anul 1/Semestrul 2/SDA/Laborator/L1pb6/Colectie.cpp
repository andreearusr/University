#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;


Colectie::Colectie() {

	this->cp = 1;
    frecv = new TElem[this->cp];
    frecv[0]=0;
	this->n = 0;
	this->m = 0;
	this->M = 0;
}

void Colectie::redim(int cp1) {

	TElem *eNou = new int[cp1];
	for (int i = 0; i < cp1; i++)
        eNou[i] = 0;


    for (int i = 0; i < this->cp; i++)
        eNou[i] = frecv[i];


	delete[] frecv;
	frecv = eNou;
	this->cp = cp1;
}

void Colectie::adauga(TElem e) {

    if(this->n==0)
    {
        //this->m=0;
        //this->M=0;
        this->cp=1;
        frecv[0]=0;

        this->m = e;
        this->M = e;
        int m1 = e;
        int M1 = e;
        frecv[0]=1;
        this->n++;
    }

    else{
        if (e < this->m)
            {
            int m1=e;
            int M1=this->M;
            int cp1 = M1- m1 + 1;

            int cpp = this->cp;
            redim(cp1);

            for(int i=cpp-1; i>=0; i--)
                frecv[i+m-m1] = frecv[i];

            for(int i=m-m1-1; i>0; i--)
                frecv[i]=0;
            frecv[0]=1;
            this->n++;
            this->m = m1;
            this->M = M1;
            return;
            }

        if(e > this->M)
            {
            int M1=e;
            int m1=this->m;
            int cp1 = M1- m1 + 1;

            int cpp = this->cp;
            redim(cp1);

            for(int i=cpp; i<cp1-1; i++)
                frecv[i]=0;

            frecv[cp1-1]=1;
            this->n++;
            this->m = m1;
            this->M = M1;
            return;
            }

        if(e>=this->m && e<=this->M)
            {
            frecv[e-this->m]++;
            this->n++;
            return;
            }

        }

}


bool Colectie::sterge(TElem e) {

    if (e>this->M || e<this->m)
    {
        if(this->n==0)
            {
            //this->m=0;
            //this->M=0;
            this->cp=1;
            frecv[0]=0;
            }
        return false;
    }


    if (this->frecv[e-m] != 0)
        {

            if(e != this->m && e != this->M)
            {
            this->frecv[e-m]--;
            this->n--;
            return true;
            }

            if(e==this->m){
                if(this->frecv[e-m]==1)
                {
                this->frecv[e-m]--;
                this->n--;
                for(int j=0; j<this->cp; j++)
                    {
                    if (this->frecv[j] != 0)
                        {
                        this->m = e+j;
                        this->cp = this->M - this->m + 1;
                        for(int k=0; k<cp; k++)
                            frecv[k]=frecv[k+j];
                        return true;
                        }
                    return true;
                    }
                }

                if(this->frecv[e-m]>1){
                    this->frecv[e-m]--;
                    this->n--;
                    return true;
                    }
            }

            else if(e==this->M)
            {
                if(this->frecv[e-m]==1)
                {
                    this->frecv[e-m]--;
                    this->n--;
                    for(int j=this->cp-2; j>=0; j--)
                    {
                        if (this->frecv[j]!=0)
                        {
                        this->M= j+this->m;
                        this->cp = this->M - this->m + 1;
                        return true;
                        }
                    return true;
                    }
                }

                if(this->frecv[e-m]>1)
                {
                    this->frecv[e-m]--;
                    this->n--;
                    return true;
                }
            }
        }

    if (this->frecv[e-m] == 0)
        return false;

}


bool Colectie::cauta(TElem e) const {

    if (e > this->M || e < this->m)
        return false;
    else if(e>=this->m && e<=this->M)
    {
        if(this->frecv[e-m]==0)
            return false;
    }
    return true;
}

int Colectie::nrAparitii(TElem e) const{
    if (e > this->M || e < this->m)
        return 0;
    else if (e>=this->m && e<=this->M)
        return this->frecv[e-m];
}


int Colectie::dim() const {
	return this->n;
}


bool Colectie::vida() const {
	if (this->n==0) return true;
	return false;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    delete[] frecv;
}
