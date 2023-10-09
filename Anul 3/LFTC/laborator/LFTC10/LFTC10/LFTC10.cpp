
#include <iostream>
#include <string>
#include "Gramatica.cpp"
using namespace std;

int main()
{
	Gramatica gramatica = Gramatica("input.txt");

	string neterminal;
	cout << "Dati neterminalul: ";
	cin.clear(); cin.sync();
	getline(cin, neterminal);

	gramatica.reguliProductieNeterminal(neterminal);
}
