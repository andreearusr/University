//P1- calculeaza perimetrul si aria cercului de o raza data
#include <iostream>
using namespace std;

int main()
{
	//definire variabile si constante
	const double PI = 3.14;
	int raza;
	double perimetrul, aria;	

	cout << "---Program de calculare a perimetrului si ariei unui cerc---" << endl;
	//citire raza cerc
	cout << "Dati raza cercului: ";
	cin >> raza;

	//calcul perimetru si arie
	perimetrul = 2 * PI * raza;
	aria = PI * raza * raza;

	//afisare
	cout << "Perimetrul cercului este " << perimetrul << endl;
	cout << "Aria cercului este " << aria << endl;
	return 0;
}