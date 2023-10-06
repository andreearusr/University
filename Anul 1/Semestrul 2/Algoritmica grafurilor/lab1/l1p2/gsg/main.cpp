#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("graf3.txt");
const int maxx = 100000;
int a1[100][100], k, n1, m;

void cit()
{
	int i, j, x;
	fin >> n1 >> m;
	for (i = 1; i <= n1; i++)
		for (j = i + 1; j <= n1; j++)
			a1[i][j] = a1[j][i] = maxx;
	for (x = 1; x <= m; x++)
	{
		fin >> i >> j;
		a1[i][j] = 1;
		a1[j][i] = 1;
	}
}

void rf()
{
	int i, j, k;
	for (k = 1; k <= n1; k++)
		for (i = 1; i <= n1; i++)
			for (j = 1; j <= n1; j++)
				if (i != j)
					if (a1[i][j]>a1[i][k] + a1[k][j])
						a1[i][j] = a1[i][k] + a1[k][j];
}

void afis()
{
	int i, j;
	for (i = 1; i <= n1; i++)
	{
		for (j = 1; j <= n1; j++)
			if (a1[i][j] != maxx) cout << a1[i][j] <<" ";
			else cout <<"inf ";
			cout <<"\n";
	}
}

int main()
{
	cit();
	rf();
	afis();
	return 0;
}
