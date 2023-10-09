#include <iostream>
#include "ui.h"
#include "validare.h"
#include <vector>
#include <map>
using std::cin;
using std::cout;

void Consola::print(vector<Medicament>& medicamente) const{

	if (medicamente.size() == 0)
	{
		cout << "Nu exista medicamente!\n";
		return;
	}
	else {
		for (const auto& m : medicamente)
		{
			cout << "Denumire: " << m.get_denumire() << "\n";
			cout << "Pret: " << m.get_pret() << "\n";
			cout << "Producator: " << m.get_producator() << "\n";
			cout << "Substanta activa: " << m.get_substanta() << "\n";
			cout << "\n";
		}
	}
}

void Consola::meniu() const
{
	cout << "\n\tGestiune farmacie\n";
	cout << "1. Adaugare medicament\n";
	cout << "2. Stergere medicament\n";
	cout << "3. Modificare medicament\n";
	cout << "4. Afisare medicamente\n";
	cout << "5. Cautare medicament\n";
	cout << "6. Filtrare medicamente\n";
	cout << "7. Sortare medicamente\n";
	cout << "8. Adauga medicament pe reteta\n";
	cout << "9. Goleste reteta\n";
	cout << "10. Genereaza reteta\n";
	cout << "11. Raport\n";
	cout << "0. Iesire\n";
}
void Consola::run()
{
	int cmd=0;
	while (1)
	{

		meniu();
		cout << "Dati comanda: "; cin >> cmd; cout << "\n";
		if (cmd == 1) {
			string den, prod, subst;
			float pret;
			cout << "Dati denumirea: ";
			cin.get();
			getline(cin, den);
			cout << "Dati producatorul: ";
			getline(cin, prod);
			cout << "Dati substanta activa: ";
			getline(cin, subst);
			cout << "Dati pretul: "; cin >> pret;
			try {
				srv.add_medicament(Medicament(den, prod, subst, pret));
				cout << "Medicament adaugat cu succes!\n";
			}
			catch (const RepoException&  ex) {
				cout << ex.getMessage();
			}
			catch (const ValidException&  ex)
			{
				cout << ex.getMessage();
			}
		}

		else if (cmd == 2) {
			string den;
			cout << "Dati denumirea: ";
			cin.get();
			getline(cin, den);
			try {
				srv.delete_medicament(den);
				cout << "Medicament sters cu succes!\n";

			}
			catch (const RepoException&  ex) {
				cout << ex.getMessage();
			}
			catch (const ValidException&  ex)
			{
				cout << ex.getMessage();
			}
		}

		else if (cmd == 3) {
			string den, den_n, prod_n, subst_n;
			float pret_n;
			cout << "Dati denumirea: ";
			cin.get();
			getline(cin, den); 
			cout << "Dati denumirea noua: ";
			getline(cin, den_n); 
			cout << "Dati producatorul nou: "; 
			getline(cin, prod_n);
			cout << "Dati substanta activa noua:"; 
			getline(cin, subst_n);
			cout << "Dati pretul nou: "; cin >> pret_n;

			try {
				srv.update_medicament(den, Medicament(den_n, prod_n, subst_n, pret_n));
				cout << "Medicament actualizat cu succes!\n";
			}
			catch (const RepoException& ex) {
				cout << ex.getMessage();
			}
			catch (const ValidException& ex)
			{
				cout << ex.getMessage();
			}

		}

		else if (cmd == 4) {
			print(srv.get_all());
		}

		else if (cmd == 5) {
			string den;
			cout << "Dati denumirea: ";
			cin.get();
			getline(cin, den); 
			
			try{
				Medicament med = srv.find_medicament(den);
				cout << "Denumire: " << med.get_denumire() << "\n";
				cout << "Pret: " << med.get_pret() << "\n";
				cout << "Producator: " << med.get_producator() << "\n";
				cout << "Substanta activa: " << med.get_substanta() << "\n";
				}

			catch (const RepoException& ex) {
				cout << ex.getMessage();
			}
		}

		else if (cmd == 6) {
			cout << "1. Dupa pret\n";
			cout << "2. Dupa substanta activa\n";
			cout << "Dati comanda: "; cin >> cmd;
			if (cmd == 1) {
				float pret;
				cout << "Dati un pret: "; cin >> pret;
				if (pret < 0)
				{
					cout<<"Pret invalid!\n";
				}
				vector<Medicament> meds = srv.filter_pret( pret);
				print(meds);
			}
			else if (cmd == 2) {
				string subst;
				cout << "Dati substanta activa: ";
				cin.get();
				getline(cin, subst);
				try {
					vector<Medicament> meds = srv.filter_subst(subst);
					print(meds);
				}
				catch (const ValidException& ex)
				{
					cout << ex.getMessage();
				}
			}
			else {
				cout << "Comanda invalida!\n";
				return;
			}
		}

		else if (cmd == 7)
		{
		cout << "1. Dupa denumire\n2. Dupa producator\n3. Dupa substanta activa + pret\nDati comanda: ";
		cin >> cmd;
		if (cmd == 1)
		{
			vector<Medicament> meds = srv.sort_denumire();
			print(meds);
		}

		else if (cmd == 2)
		{
			vector<Medicament> meds = srv.sort_producator();
			print(meds);
		}
		else if (cmd == 3)
		{
			vector<Medicament> meds = srv.sort_subst_pret();
			print(meds);
		}


		else {
			cout << "Comanda invalida!\n";
			return;
		}

		}

		else if (cmd == 8)
		{
			string den;
			cout << "Dati denumirea: ";
			cin.get();
			getline(cin, den);
			try {
				srv.adauga_reteta(den);
				cout << "Medicament adaugat in reteta!\n";
			}
			catch (const RepoException& ex) {
				cout << ex.getMessage();
			}

			catch (const ValidException& ex)
			{
				cout << ex.getMessage();
			}
			cout <<"\nNumar medicamente din reteta: "<< srv.dim_reteta();
		}

		else if (cmd == 9)
		{
			srv.goleste_reteta();
			cout << "Reteta golita!\n";
			cout << "\nNumar medicamente din reteta: " << srv.dim_reteta();
		}

		else if (cmd == 10)
		{
			int nr;
			cout << "Dati numarul de medicamente cu care sa se populeze reteta";
			cin >> nr;
			if (nr <= 0)
			{
				cout << "Numar invalid!\n";
				return;
			}
			else {
				srv.genereaza_reteta(nr);
				cout << "Reteta generata!\n";
			}
			cout << "\nNumar medicamente din reteta: " << srv.dim_reteta();
		}
		else if (cmd == 11)
		{
		std::map<string, DTO> rez = srv.producator();

		for (auto& elem : rez)
		{
			cout << "Tip:" << elem.first << " " <<"Numar produse:"<< elem.second.get_count();
			cout << "\n";
		}

		}

		else if (cmd == 0)
		{
			cout << "Goodbye!\n";
			return;
		}

		else {
			cout << "Comanda invalida!\n";
			return;
		}

	}
}