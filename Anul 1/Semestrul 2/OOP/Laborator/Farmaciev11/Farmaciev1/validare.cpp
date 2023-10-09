#pragma once
#include "validare.h"
#include <assert.h>


string ValidException::getMessage() const{
	return msg;
}

void Validator:: validare_med(const Medicament& med) {
	string erori;
	if (med.get_denumire().size() == 0)
		erori += "Denumire medicament invalida!\n";
	if (med.get_pret()<0)
		erori += "Pret medicament invalid!\n";
	if (med.get_producator().size() == 0)
		erori += "Producator medicament invalid!\n";
	if (med.get_substanta().size() == 0)
		erori += "Substanta medicament invalida!\n";
	if(erori.size()!=0)
		throw ValidException(erori);
}

void Validator::validare_den(const string& denumire) {
	string erori;
	if (denumire.size() == 0)
		erori += "Denumire medicament invalida!\n";
	if (erori.size() != 0)
		throw ValidException(erori);}

void Validator::validare_subst(const string& substanta) {
	string erori;
	if (substanta.size() == 0)
		erori += "Substanta medicament invalida!\n";
	if (erori.size() != 0)
		throw ValidException(erori);}
