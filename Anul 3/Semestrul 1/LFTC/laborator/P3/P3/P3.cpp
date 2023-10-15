//P3- calculeaza suma a n numere citite de la tastatura
#include <iostream>
using namespace std;

int main()
{
	//declarare variabile
    int suma = 0, n, numar;

	cout << "---Program de calculare a sumei a n numere citite de la tastatura---" << endl;
	cout << "Dati numarul n: ";
	cin >> n;

	//citire numere si calculare suma
	cout << "Citire numere:" << endl;
	while (n != 0) {
		cout << "numar= ";
		cin >> numar;
		suma = suma + numar;
		n = n - 1;
	}

	//afisare
	cout << "Suma celor " << n << " numere este: " << suma;
	return 0;
}
