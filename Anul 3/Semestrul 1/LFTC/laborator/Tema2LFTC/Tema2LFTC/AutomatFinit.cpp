
#include<vector>
#include<string>
#include <map>
#include <list>
using namespace std;

class AutomatFinit {

private:
	vector<string> stari;
	vector<string> alfabet;
	map<string, multimap<string, string>> tranzitii;
	string stareInitiala;
	vector<string> stariFinale;

public:
	AutomatFinit() {}

	AutomatFinit(vector<string> stari, vector <string> alfabet, map<string, multimap<string, string>> tranzitii, string stareInitiala, vector<string> stariFinale) {
		this->stari = stari;
		this->alfabet = alfabet;
		this->tranzitii = tranzitii;
		this->stareInitiala = stareInitiala;
		this->stariFinale = stariFinale;
	}

	vector<string> getStari() {
		return this->stari;
	}

	vector<string> getAlfabet() {
		return this->alfabet;
	}

	map<string, multimap<string, string>> getTranzitii() {
		return this->tranzitii;
	}

	string getStareInitiala() {
		return this->stareInitiala;
	}

	vector<string> getStariFinale() {
		return this->stariFinale;
	}

};