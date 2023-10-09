#include <string>
#include <assert.h>
#include "domain.h"


string Medicament::get_denumire() const {
	return denumire;
}

string Medicament::get_producator() const {
	return producator;
}

string Medicament::get_substanta() const {
	return substanta;
}

float Medicament::get_pret() const noexcept{
	return pret;
}

