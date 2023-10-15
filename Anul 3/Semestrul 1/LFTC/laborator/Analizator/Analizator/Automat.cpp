#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <list>
#include <sstream>
#include <regex>
#include <fstream>
#include "AutomatFinit.cpp"

using namespace std;

class Automat {

private:
	string fileName;
	AutomatFinit automatFinit;
	bool automatFinitDeterminist;

public:
	Automat() {}
	Automat(string fileName) {
		this->fileName = fileName;
		this->automatFinit = AutomatFinit();
		this->automatFinitDeterminist = false;
	}

	vector<string> splitLine(string line, char separator) {
		vector<string> words;
		string word;
		istringstream ss(line);

		while (getline(ss, word, separator))
			words.push_back(word);

		return words;
	}

	vector<string> getStariTastatura(string linie) {
		vector<string> stari = vector<string>();
		vector<string> stariTastatura = splitLine(linie, ' ');

		for (auto stare : stariTastatura) {
			//if (regex_match(stare, regexStare))
				stari.push_back(stare);
			//else
			//	cout << "stare incorecta: " << stare << endl;
		}

		return stari;
	}

	vector<string> getAlfabetTastatura(string linie) {
		vector<string> alfabet = vector<string>();
		vector<string> alfabetTastatura = splitLine(linie, ' ');

		for (auto alf : alfabetTastatura) {
			//if (regex_match(alf, regexLitera) || regex_match(alf, regexCifra))
				alfabet.push_back(alf);
			//else
			//	cout << "alfabet incorect: " << alf << endl;
		}

		return alfabet;
	}

	map<string, multimap<string, string>> getTranzitiiTastatura(string linie) {
		map<string, multimap<string, string>> tranzitii;
		string key1, key2, val;
		vector<string> tranzitiiTastatura = splitLine(linie, ';');
		automatFinitDeterminist = true;
		for (auto el : tranzitiiTastatura) {
			vector<string> tranzitie = splitLine(el, ' ');
			//if (regex_match(tranzitie[0], regexStare) &&
			//	(regex_match(tranzitie[1], regexLitera) || regex_match(tranzitie[1], regexCifra)) &&
			//	regex_match(tranzitie[2], regexStare)) {
				key1 = tranzitie[0];
				key2 = tranzitie[1];
				val = tranzitie[2];

				/*if (tranzitii[key1][key2].size() > 0)
				      automatFinitDeterminist = false;

			    tranzitii[key1][key2] = val;*/

				if (tranzitii[key1].find(key2) != tranzitii[key1].end())
					automatFinitDeterminist = false;

				tranzitii[key1].insert(pair<string, string>(key2, val));
		//	}
		//	else
		//		cout << "tranzitie incorecta: " << el << endl;
		}

		return tranzitii;
	}

	string getStareInitialaTastatura(string linie) {
		string stareInitiala = "";
		//vector<string> stareInitialaTastatura = splitLine(linie, ' ');
		if (linie.size() > 1) {
			cout << "numar stari initiale > 1 !";
			return stareInitiala;
		}
		stareInitiala = linie;
		return stareInitiala;
	}

	vector<string> getStariFinaleTastatura(string linie) {
		vector<string> stariFinale = vector<string>();
		vector<string> stariFinaleTastatura = splitLine(linie, ' ');

		for (auto stare : stariFinaleTastatura) {
			//if (regex_match(stare, regexStare))
				stariFinale.push_back(stare);
		//	else
		//		cout << "stare finala incorecta: " << stare << endl;
		}

		return stariFinale;
	}

	void citireFisier() {
		ifstream fisierInput(this->fileName);
		string linie;

		vector<string> stari;
		vector<string> alfabet;
		string stareInitiala;
		vector<string> stariFinale;
		map<string, multimap<string, string>> tranzitii;

		while (getline(fisierInput, linie)) {
			//cout << linie << endl;
			char simbol = linie[0];

			if (simbol == 'Q') {
				stari = getStariTastatura(linie.substr(3, linie.size()));
				continue;
			}
			else if (simbol == 'A') {
				alfabet = getAlfabetTastatura(linie.substr(3, linie.size()));
				continue;
			}
			else if (simbol == 'T') {
				tranzitii = getTranzitiiTastatura(linie.substr(3, linie.size()));
				continue;
			}
			else if (simbol == 'I') {
				stareInitiala = getStareInitialaTastatura(linie.substr(3, linie.size()));
				if (stareInitiala == "") {
					cout << "stare initiala negasita -- eroare!";
					break;
				}
				continue;
			}
			else if (simbol == 'F') {
				stariFinale = getStariFinaleTastatura(linie.substr(3, linie.size()));
				continue;
			}
			else {
				cout << "Eroare - simbol incorect!" << endl;
				break;
			}
		}
		this->automatFinit = AutomatFinit(stari, alfabet, tranzitii, stareInitiala, stariFinale);
	}


	bool verificaSecventa(string secventa) {
		map<string, multimap<string, string>> tranzitii = automatFinit.getTranzitii();
		string stareInitiala = automatFinit.getStareInitiala();
		vector<string> stariFinale = automatFinit.getStariFinale();

		string stareCurenta = stareInitiala;
		int t = 0;
		for (auto ch : secventa) {
			multimap<string, string> myMap = tranzitii[stareCurenta];
			map<string, string>::iterator it;
			string caracter(1, ch);
			it = myMap.find(caracter);

			if (it != myMap.end()) {
				stareCurenta = it->second;
				//cout << stareCurenta << " ";
			}
			else {
				t = 1;
				break;
			}
		}

		if (t == 0) {
			if (find(stariFinale.begin(), stariFinale.end(), stareCurenta) != stariFinale.end()) {
				return true;
			}
			else {
				return false;
			}
		}

		return false;
	};
	void secventaAcceptata() {
		/*if (automatFinitDeterminist == false)
		{
			cout << "automatul este finit nedeterminist! " << endl;
			return;
		}*/

		string secventa;
		cout << "Dati o secventa: ";
		cin.ignore();
		getline(cin, secventa);
		cout << endl;

		bool rez = verificaSecventa(secventa);
		if (rez == true)
			cout << "secventa este acceptata";
		else
			cout << "secventa nu este acceptata";
		cout << endl;
	};


	string celMaiLungPrefix(string secventa) {
		/*if (automatFinitDeterminist == false)
		{
			cout << "automatul este finit nedeterminist! " << endl;
			return "";
		}*/

		/*string secventa;
		cout << "Dati o secventa: ";
		cin.ignore();
		getline(cin, secventa);
		cout << endl;*/

		int t = 0;
		for (int i = secventa.length() - 1; i >= 0; i -= 1) {
			if (verificaSecventa(secventa)) {
				cout << "Cel mai lung prefix este: " << secventa << endl;
				t = 1;
				return secventa;
			}
			secventa = secventa.substr(0, i);
		}

		if (t == 0) {
			cout << "Nu am gasit cel mai lung prefix -- secventa nu este acceptata de catre automat" << endl;
			return "";
		}
	};







};