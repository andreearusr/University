
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;

class RProductie {

private:
	string stanga;
	string dreapta;

public:
	RProductie(string stanga, string dreapta) {
		this->stanga = stanga;
		this->dreapta = dreapta;
	}

	string getStanga() {
		return this->stanga;
	}

	string getDreapta() {
		return this->dreapta;
	}
};

class Gramatica {
private:
	vector<RProductie> reguliProductie;

public:
	Gramatica(string fisierInput) {
		citesteDinFisier(fisierInput);
	}

	vector<RProductie> getReguliProductie() {
		return this->reguliProductie;
	}

	vector<string> splitLine(string line, char separator) {
		vector<string> words;
		string word;
		istringstream ss(line);

		while (getline(ss, word, separator))
			words.push_back(word);

		return words;
	}

	void citesteDinFisier(string fisierInput) {
		ifstream fisier(fisierInput);
		string linie;

		while (getline(fisier, linie)) {
			//cout << linie << endl;
			vector<string> reguli = splitLine(linie, ' ');
			RProductie regulaProductie = RProductie(reguli[0], reguli[2]);
			reguliProductie.push_back(regulaProductie);
		}
	}

	void reguliProductieNeterminal(string neterminal) {
		for (RProductie rp : getReguliProductie()) {
			//cout << "stanga " << rp.getStanga() << " dreapta: " << rp.getDreapta() << endl; 

			if (rp.getStanga() == neterminal) {
				cout << rp.getStanga() << " -> " << rp.getDreapta() << endl;
			}
			else {
				for (int i = 0; i < rp.getDreapta().length(); i++) {
					if (rp.getDreapta()[i] == neterminal[0]) {
						cout << rp.getStanga() << " -> " << rp.getDreapta() << endl;
					}
				}
			}
		}
	}
};