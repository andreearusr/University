#include <string.h>
#include <ctype.h>
#include "domain.h"

// Verifica daca un string este "tip", "suprafata", "adresa" sau "pret" si returneaza
//		0 - daca stringul nu este unul dintre cele amintite sau stringul vid
//		1 - daca stringul este unul dintre cele de mai sus
// Date de intrare: un string
int validare_criteriu(char criteriu[])
{
	if (strlen(criteriu) == 0 || (strlen(criteriu) > 0 &&
		(_stricmp(criteriu, "tip") != 0 && _stricmp(criteriu, "suprafata") != 0 && _stricmp(criteriu, "adresa") != 0 && _stricmp(criteriu, "pret") != 0)))
		return 0;
	return 1;
}


// Verifica daca un string este "casa", "apartament" sau "teren" si returneaza
//		0 - daca stringul nu este unul dintre cele amintite sau stringul vid
//		1 - daca stringul este unul dintre cele de mai sus
// Date de intrare: un string
int validare_tip(char tip[])
{
	if (strlen(tip) == 0 || (strlen(tip) > 0 &&
		(_stricmp(tip, "casa") != 0 && _stricmp(tip, "apartament") != 0 && _stricmp(tip, "teren") != 0)))
		return 0;
	return 1;
}

// Verifica daca un numar real este strict pozitiv sau nu si returneaza
//		0 - daca numarul este mai mic egal ca 0
//		1 - daca numarul este mai mare strict decat 0
// Date de intrare: un numar real
int validare_numar(double nr)
{
	if (nr <= 0)
		return 0;
	return 1;
}

// Functie care valideaza o oferta de tip Oferta
//		Date de intrare: o oferta de tip Oferta
//		returneaza: o variabila de tip Informatii care are toate informatiile despre eroare (text si cod)
//			info.cod = 0, daca oferta are toate campurile valide
//			info.cod = 1, daca oferta are campuri invalide:
//				- oferta.tip = INVALID daca este string vid sau NU este unul dintre string-urile: ["casa", "teren", "apartament"]
//				- oferta.suprafata = INVALID daca este un numar mai mic sau egal cu 0
//				- oferta.adresa = INVALID daca este string vid sau NU are in componenta sa cel putin o litera sau o cifra
//				- oferta.pret = INVALID daca este un numar mai mic sau egal cu 0
Informatii validare(Oferta* oferta)
{
	char text[100] = { 0 };
	Informatii eroare;
	if (!validare_tip(oferta->tip))
		strcat(text, "Tip invalid !\n");
	if (!validare_numar(oferta->suprafata))
		strcat(text, "Suprafata invalida !\n");
	if (strlen(oferta->adresa) == 0)
		strcat(text, "Adresa invalida !\n");
	else
	{
		int ok = 0;
		for (unsigned int i = 0; i < strlen(oferta->adresa); i++)
			if (isalnum(oferta->adresa[i]))
			{
				ok = 1;
				break;
			}
		if (!ok)
			strcat(text, "Adresa invalida !\n");
	}
	if (!validare_numar(oferta->pret))
		strcat(text, "Pret invalid !\n");
	if (strlen(text) == 0)
	{
		eroare.cod = 0;
		strcpy(eroare.text, "Comanda realizata cu succes !\n");
	}
	else
	{
		eroare.cod = 1;
		strcpy(eroare.text, text);
	}
	return eroare;
}