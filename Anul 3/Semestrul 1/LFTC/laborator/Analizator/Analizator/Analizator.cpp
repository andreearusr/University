
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <map>
#include "LinkedList.cpp"
#include "Automat.cpp"
using namespace std;

Automat automatConstIntregi = Automat("inputConst.txt");
Automat automatConstReale = Automat("inputConstR.txt");
Automat automatConstString = Automat("inputConstS.txt");
Automat automatID = Automat("inputID.txt");


//functie pentru citirea liniilor din fisier
vector<string> getLines(string filename) {
	string line;
	vector<string> lines;
	ifstream fin(filename);
	if (fin.is_open())
	{
		while (getline(fin, line))
			lines.push_back(line);
		fin.close();
	}
	else cout << "File could not be opened";
	return lines;
}

//functie pentru compararea a doua
bool compare(pair<string, int>& a, pair<string, int>& b)
{
	return a.second < b.second;
}

//functie care returneaza un vector de stringuri corespunzatoare unei linii/fraze,etc
//separate prin spatiu
vector<string> splitLine(string line) {
	vector<string> words;
	string word;
	istringstream ss(line);
	while (ss >> word)
		words.push_back(word);
	return words;
}

void writeToFile(ofstream& foutCodes, map<string, int> codes) {
	//sortare crescatoare dupa codurile date
	vector<pair<string, int>> copyCodes;
	for (auto& elem : codes)
		copyCodes.push_back(elem);
	sort(copyCodes.begin(), copyCodes.end(), compare);

	//scrierea in fisier a atomilor si a codurilor corespunzatoare
	for (const auto& elem : copyCodes)
		foutCodes << elem.first << " " << elem.second << "\n";
}

void generateCodes(vector<string> lines, vector<string> keywords, vector<string> separators, vector<string> operators, ofstream &foutCodes, ofstream& foutFIP, ofstream& foutIdentifTS, ofstream& foutConstTS) {
	//definire regex-uri
	regex identif("[a-zA-Z][a-zA-Z1-9]{0,7}");
	regex const_string("[\"].*[\"]");
	regex natural_number("0|[1-9][0-9]*");
	regex double_number("(0|([1-9]*))([.][0-9]*)");

	map<string, int> codes = {};
	int code = 2;
	vector<string> words;
	string atom;
	int codTSidentif = 0;
	int codTSconst = 0;
	Node* TSidentif = NULL;
	Node* TSconst = NULL;

	//parcurgere linie cu linie
	//pentru fiecare cuvant din linie se verifica apartenenta lui la operatori,separatori,cuvinte rezervate
	//daca respecta unul din acestea, i se da un cod atomului respectiv
	//altfel, se verifica daca este identificator
	//daca e identificator, i se da codul 0
	//altfel, se verifica daca este constanta
	//daca e identiconstantaficator, i se da codul 1
	//altfel, eroare si programul se termina
	for (int i = 0; i < lines.size(); i++) {
		words = splitLine(lines[i]);
		for (int j = 0; j < words.size(); j++) {
			atom = words[j];

			if (find(operators.begin(), operators.end(), atom) != operators.end() ||
				find(separators.begin(), separators.end(), atom) != separators.end() ||
				find(keywords.begin(), keywords.end(), atom) != keywords.end()) {

				if (codes[atom] == 0) {
					codes[atom] = code;
					code += 1;
				}
				foutFIP << codes[atom] << " " << 0 << "\n";
			}
			else
				if (regex_match(atom, identif)) {
					if (codes["ID"] == 0) 
						codes["ID"] = 0;	

					codTSidentif = (*TSidentif).search(TSidentif, atom);
					if (codTSidentif == 0) 
						codTSidentif = (*TSidentif).addTSidentif(atom, &TSidentif, (*TSidentif).getCount(TSidentif));
					
					foutFIP << 0 << " " << codTSidentif << "\n";
				}
				else
					if (regex_match(atom, natural_number) || regex_match(atom, double_number) || regex_match(atom, const_string)) {
						if (codes["CONST"] == 0) 
							codes["CONST"] = 1;

						codTSconst = (*TSconst).search(TSconst, atom);
						if (codTSconst == 0) 
							codTSconst = (*TSconst).addTSconst(atom, &TSconst, (*TSconst).getCount(TSconst));

						foutFIP << 1 << " " << codTSconst << "\n";
					}
					else {
						cout << "Eroare-lexicala-la-atomul:" << atom << endl;
						writeToFile(foutCodes, codes);
						(*TSidentif).writeToFileTS(foutIdentifTS, TSidentif);
						(*TSconst).writeToFileTS(foutConstTS, TSconst);
						return;
					}
		}
	}
	/**cout << "const:----------------";
	(*TSconst).printList(TSconst);
	cout << "identif:--------------";
	(*TSidentif).printList(TSidentif);**/

	writeToFile(foutCodes, codes);
	(*TSidentif).writeToFileTS(foutIdentifTS, TSidentif);
	(*TSconst).writeToFileTS(foutConstTS, TSconst);
}

void generateCodesAnaliza(vector<string> lines, vector<string> keywords, vector<string> separators, vector<string> operators, ofstream& foutCodes, ofstream& foutFIP, ofstream& foutIdentifTS, ofstream& foutConstTS) {
	map<string, int> codes = {};
	int code = 2;
	vector<string> words;
	int codTSidentif = 0;
	int codTSconst = 0;
	Node* TSidentif = NULL;
	Node* TSconst = NULL;

	string line;
	string atom = "";
	string atomExtended = "";

	//parcurgere linie cu linie
	//pentru fiecare cuvant din linie se verifica apartenenta lui la operatori,separatori,cuvinte rezervate
	//daca respecta unul din acestea, i se da un cod atomului respectiv
	//altfel, se verifica daca este identificator
	//daca e identificator, i se da codul 0
	//altfel, se verifica daca este constanta
	//daca e identiconstantaficator, i se da codul 1
	//altfel, eroare si programul se termina
	for (int i = 0; i < lines.size(); i++) {
		line = lines[i];
		while (line.size() > 0) {

			cout << line << endl;
			if ((atom = automatID.celMaiLungPrefix(line)) != "") {
				if (find(keywords.begin(), keywords.end(), atom) != keywords.end()) {
					cout << atom << " e cuvant rezervat" << endl;

					// scriere in fip
					//int cod = AnalizatorLexical::pozitie(atom, &treeCode);
					//AnalizatorLexical::generareFip(cod, 0, outputFip);
					if (codes[atom] == 0) {
						codes[atom] = code;
						code += 1;
					}
					foutFIP << codes[atom] << " " << 0 << "\n";

				}
				else {
					cout << atom << " e identificator" << endl;

					if (codes["ID"] == 0)
						codes["ID"] = 0;

					codTSidentif = (*TSidentif).search(TSidentif, atom);
					if (codTSidentif == 0)
						codTSidentif = (*TSidentif).addTSidentif(atom, &TSidentif, (*TSidentif).getCount(TSidentif));

					foutFIP << 0 << " " << codTSidentif << "\n";

					// scriere in tabela identificator (cod 1)
					//int codTs = AnalizatorLexical::pozitie(atom, &treeId);
					//if (codTs == 0) {
					//	codTs = AnalizatorLexical::adaugaInTree(atom, &treeId);
					//}

					//// scriere in fip
					//AnalizatorLexical::generareFip(1, codTs, outputFip);
				}
			}
			else if ((atom = automatConstString.celMaiLungPrefix(line)) != "") {
				cout << atom << " e constanta string" << endl;


				// scriere in tabela constante (cod 2)
				//int codTs = AnalizatorLexical::pozitie(atom, &treeConst);
				//if (codTs == 0) {
				//	codTs = AnalizatorLexical::adaugaInTree(atom, &treeConst);
				//}
				//// scriere in fip
				//AnalizatorLexical::generareFip(2, codTs, outputFip);
				if (codes["CONST"] == 0)
					codes["CONST"] = 1;

				codTSconst = (*TSconst).search(TSconst, atom);
				if (codTSconst == 0)
					codTSconst = (*TSconst).addTSconst(atom, &TSconst, (*TSconst).getCount(TSconst));

				foutFIP << 1 << " " << codTSconst << "\n";

			}
			else if ((atom = automatConstIntregi.celMaiLungPrefix(line)) != "") {
				cout << atom << " e constanta intreaga" << endl;

				if (codes["CONST"] == 0)
					codes["CONST"] = 1;

				codTSconst = (*TSconst).search(TSconst, atom);
				if (codTSconst == 0)
					codTSconst = (*TSconst).addTSconst(atom, &TSconst, (*TSconst).getCount(TSconst));

				foutFIP << 1 << " " << codTSconst << "\n";
				// scriere in tabela constante (cod 2)
				//int codTs = AnalizatorLexical::pozitie(atom, &treeConst);
				//if (codTs == 0) {
				//	codTs = AnalizatorLexical::adaugaInTree(atom, &treeConst);
				//}
				//// scriere in fip
				//AnalizatorLexical::generareFip(2, codTs, outputFip);
			}
			else {
				atom = line[0];

				if (find(separators.begin(), separators.end(), atom) != separators.end()) {
					cout << atom << " e separator" << endl;

					if (codes["CONST"] == 0)
						codes["CONST"] = 1;

					codTSconst = (*TSconst).search(TSconst, atom);
					if (codTSconst == 0)
						codTSconst = (*TSconst).addTSconst(atom, &TSconst, (*TSconst).getCount(TSconst));

					foutFIP << 1 << " " << codTSconst << "\n";

					// scriere in fip
					/*int cod = AnalizatorLexical::pozitie(atom, &treeCode);
					AnalizatorLexical::generareFip(cod, 0, outputFip);*/
				}

				else {
					int index = 1;
					atomExtended = atom;

					bool isOperator = false;

					while (find(operators.begin(), operators.end(), atomExtended) != operators.end()) {
						atom = atomExtended;
						atomExtended += line[index];
						index++;
						isOperator = true;
					}

					if (isOperator) {
						cout << atom << " e operator" << endl;

						if (codes["CONST"] == 0)
							codes["CONST"] = 1;

						codTSconst = (*TSconst).search(TSconst, atom);
						if (codTSconst == 0)
							codTSconst = (*TSconst).addTSconst(atom, &TSconst, (*TSconst).getCount(TSconst));

						foutFIP << 1 << " " << codTSconst << "\n";

						// scriere in fip
						/*int cod = AnalizatorLexical::pozitie(atom, &treeCode);
						AnalizatorLexical::generareFip(cod, 0, outputFip);*/
					}
					else {
						cout << "Eroare lexicala la linia " << i << " caracter " << atom << endl;
						writeToFile(foutCodes, codes);
						(*TSidentif).writeToFileTS(foutIdentifTS, TSidentif);
						(*TSconst).writeToFileTS(foutConstTS, TSconst);
						return;
					}
				}
			}
			line = line.substr(atom.size());
		}

		cout << "const:----------------" << endl;
		(*TSconst).printList(TSconst);
		cout << "identif:--------------" << endl;
		(*TSidentif).printList(TSidentif);

		writeToFile(foutCodes, codes);
		(*TSidentif).writeToFileTS(foutIdentifTS, TSidentif);
		(*TSconst).writeToFileTS(foutConstTS, TSconst);

	}
}

int main()
{
	ofstream foutCodes("codAtomi.txt");	
	ofstream foutFIP("fip.txt");
	ofstream identifTS("TSidentif.txt");
	ofstream constTS("TSconst.txt");

	vector<string> keywords = getLines("cuvinteCheie.txt");
	vector<string> separators = getLines("separatori.txt");
	vector<string> operators = getLines("operatori.txt");
	vector<string> lines = getLines("P2.txt");

	for (int i = 0; i < separators.size(); i++) {
		cout << separators[i] << "";
	}

	//automatConstIntregi.citireFisier();
	////automatConstReale.citireFisier();
	//automatConstString.citireFisier();
	//automatID.citireFisier();

	generateCodes(lines, keywords, separators, operators, foutCodes, foutFIP, identifTS, constTS);
	return 0;
}