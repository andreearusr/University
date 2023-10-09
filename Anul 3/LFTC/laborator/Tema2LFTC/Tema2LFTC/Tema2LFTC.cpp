

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "AutomatFinit.cpp"
#include <map>
#include <list>
#include <sstream>
#include <regex>
#include <utility>
using namespace std;

AutomatFinit automatFinit = AutomatFinit();
regex regexStare("[a-zA-Z]{1,}");
regex regexLitera("[a-zA-Z]");
regex regexCifra("[0-9]");

bool automatFinitDeterminist;

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
		if (regex_match(stare, regexStare))
			stari.push_back(stare);
		else
			cout << "stare incorecta: " << stare << endl;
	}

	return stari;
}

vector<string> getAlfabetTastatura(string linie) {
	vector<string> alfabet = vector<string>();
	vector<string> alfabetTastatura = splitLine(linie, ' ');

	for (auto alf : alfabetTastatura) {
		if (regex_match(alf, regexLitera) || regex_match(alf, regexCifra))
			alfabet.push_back(alf);
		else
			cout << "alfabet incorect: " << alf << endl;
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
		if (regex_match(tranzitie[0], regexStare) &&
			(regex_match(tranzitie[1], regexLitera) || regex_match(tranzitie[1], regexCifra)) &&
			regex_match(tranzitie[2], regexStare)) {
			key1 = tranzitie[0];
			key2 = tranzitie[1];
			val = tranzitie[2];

			/*if (tranzitii[key1][key2].size() > 0)
				automatFinitDeterminist = false;
				
			tranzitii[key1][key2] = val;*/	

			if (tranzitii[key1].find(key2) != tranzitii[key1].end())
				automatFinitDeterminist = false;

			tranzitii[key1].insert(pair<string, string>(key2, val));
		}
		else
			cout << "tranzitie incorecta: " << el << endl;
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
		if (regex_match(stare, regexStare))
			stariFinale.push_back(stare);
		else
			cout << "stare finala incorecta: " << stare << endl;
	}

	return stariFinale;
}

vector<string> citireStari() {
	string linie;
	cout << "Dati starile: ";
	cin.ignore();
	getline(cin, linie);
	vector<string> stari = getStariTastatura(linie);
	return stari;
}

vector<string> citireAlfabet() {
	string linie;
	cout << "Dati alfabetul: ";
	cin.clear(); cin.sync();
	getline(cin, linie);
	vector<string> alfabet = getAlfabetTastatura(linie);
	return alfabet;
}

map<string, multimap<string, string>> citireTranzitii() {
	string linie;
	cout << "Dati tranzitiile: ";
	cin.clear(); cin.sync();
	getline(cin, linie);
	map<string, multimap<string, string>> tranzitii = getTranzitiiTastatura(linie);
	return tranzitii;
}

string citireStareInitiala() {
	string linie;
	cout << "Dati starea initiala: ";
	cin.clear(); cin.sync();
	getline(cin, linie);
	string stareInitiala = getStareInitialaTastatura(linie);
	return stareInitiala;
}

vector<string> citireStariFinale() {
	string linie; 
	cout << "Dati starile finale: ";
	cin.clear(); cin.sync();
	getline(cin, linie);
	vector<string> stariFinale = getStariFinaleTastatura(linie);
	return stariFinale;
}


void citireTastatura() {

	vector<string> stari = citireStari();
	cout << endl;

	vector<string> alfabet = citireAlfabet();
	cout << endl;

	map<string, multimap<string, string>> tranzitii = citireTranzitii();
	cout << endl;

	string stareInitiala = citireStareInitiala();
	if (stareInitiala == "") {
		cout << "stare initiala negasita -- eroare!";
		return;
	}
	cout << endl;

	vector<string> stariFinale = citireStariFinale();
	cout << endl;

	automatFinit = AutomatFinit(stari, alfabet, tranzitii, stareInitiala, stariFinale);
}


void citireFisier() {
	ifstream fisierInput("inputAFD.txt");
	string linie;

	vector<string> stari;
	vector<string> alfabet;
	string stareInitiala;
	vector<string> stariFinale;
	map<string, multimap<string, string>> tranzitii;

	while (getline(fisierInput, linie)) {
		cout << linie << endl;
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
	automatFinit = AutomatFinit(stari, alfabet, tranzitii, stareInitiala, stariFinale);
}

void afiseazaStari() {
	vector<string> stari = automatFinit.getStari();
	for (auto el : stari) {
		cout << el << " ";
	}
	cout << endl;
}

void afiseazaAlfabet() {
	vector<string> alfabet = automatFinit.getAlfabet();
	for (auto el : alfabet) {
		cout << el << " ";
	}
	cout << endl;
}

void afiseazaTranzitii() {
	map<string, multimap<string, string>> tranzitii = automatFinit.getTranzitii();
	for (auto outer = tranzitii.begin(); outer != tranzitii.end(); outer++) {
		cout << outer->first << "->";
		auto inner_map = outer->second;

		for (auto inner_iterator = inner_map.begin(); inner_iterator != inner_map.end(); inner_iterator++) {
			cout << inner_iterator->first << "->"; 
			cout << inner_iterator->second; 
			cout << endl;
		}
		cout << endl;
	}
}

void afiseazaStariFinale() {
	vector<string> stariFinale = automatFinit.getStariFinale();
	for (auto el : stariFinale) {
		cout << el << " ";
	}
	cout << endl;
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


void celMaiLungPrefix() {
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

	int t = 0;
	for (int i = secventa.length() - 1; i >= 0; i-=1) {
		if (verificaSecventa(secventa)) {
			cout << "Cel mai lung prefix este: " << secventa << endl;
			t = 1;
			return;
		}
		secventa = secventa.substr(0, i);
	}

	if (t == 0)
		cout << "Nu am gasit cel mai lung prefix -- secventa nu este acceptata de catre automat" << endl;
};

void afiseazaOptiuni() {
	cout << "Optiuni:" << endl;
	cout << "1: Multimea starilor" << endl;
	cout << "2: Alfabetul" << endl;
	cout << "3: Tranzitiile" << endl;
	cout << "4: Multimea starilor finale" << endl;
	cout << "5: Verifica secventa" << endl;
	cout << "6: Cel mai lung prefix al unei secvente" << endl;
	cout << "7: Inchide" << endl;
}

void afiseazaSubmeniu() {
	string cmd;
	while (true) {
		afiseazaOptiuni();;
		cin >> cmd;
		if (cmd == "1") {
			cout << "Multimea starilor: " << endl;
			afiseazaStari();
			continue;
		}
		else if (cmd == "2") {
			cout << "Alfabetul: " << endl;
			afiseazaAlfabet();
			continue;
		}
		else if (cmd == "3") {
			cout << "Tranzitiile: " << endl;
			afiseazaTranzitii();
			continue;
		}
		else if (cmd == "4") {
			cout << "Multimea starilor finale: " << endl;
			afiseazaStariFinale();
			continue;
		}
		else if (cmd == "5") {
			cout << "Verifica secventa: " << endl;
			secventaAcceptata();
			continue;
		}
		else if (cmd == "6") {
			cout << "Cel mai lung prefix al unei secvente: " << endl;
			celMaiLungPrefix();
			continue;
		}
		else if (cmd == "7") {
			cout << "Byee" << endl;
			break;
		}
		else {
			cout << "Optiune incorecta!" << endl;
		}
	}
}

void afiseazaMeniu() {
	cout << "Cititi elementele unui automat finit:" << endl;
	cout << "1: De la tastatura" << endl;
	cout << "2: Din fisier" << endl;
	cout << "3: Inchide" << endl;
}

int main()
{
	string cmd;
	while (true) {
		afiseazaMeniu();;
		cin >> cmd;
		if (cmd == "1") {
			cout << "Citire de la tastatura" << endl;
			citireTastatura();
			afiseazaSubmeniu();
		}
		else if (cmd == "2") {
			cout << "Citire din fisier" << endl;
			citireFisier();
			afiseazaSubmeniu();
		}
		else if (cmd == "3") {
			cout << "Byeee" << endl;
			break;
		}
		else {
			cout << "Optiune incorecta!" << endl;
		}
	}
}
