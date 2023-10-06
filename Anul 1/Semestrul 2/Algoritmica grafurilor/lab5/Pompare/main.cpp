#include <iostream>
#include <fstream>

using namespace std;


void init_graf(int** g, int v)
{
	for (int i = 0; i < v; ++i)
		for (int j = 0; j < v; ++j)
			g[i][j] = 0;
}


void distruge_graf(int** g, int v)
{
	for (int i = 0; i < v; ++i)
		delete[] g[i];
	delete g;
}


void initializare_preflux(int** g, int** rg, int v, int s, int d, int* h, int* e)
{
	for (int i = 0; i < v; ++i)
	{
		e[i] = 0;
		h[i] = 0;
	}
	h[s] = v;

	for (int i = 0; i < v; ++i)
	{
		if (g[s][i] > 0)
		{
			rg[s][i] -= g[s][i];
			rg[i][s] += g[s][i];
			e[i] = g[s][i];
			e[s] -= g[s][i];
		}
	}
}


void pompare(int** rg, int e[], int u, int v)
{
	int delta_f = min(e[u], rg[u][v]);
	rg[u][v] -= delta_f;
	rg[v][u] += delta_f;
	e[u] -= delta_f;
	e[v] += delta_f;
}


void inaltare(int** rg, int h[], int v, int u)
{
	int min = INT_MAX;
	for (int i = 0; i < v; ++i)
	{
		if (h[i] < min && rg[u][i] > 0)
			min = h[i];
	}
	h[u] = 1 + min;
}


void pompare_preflux(int** g, int v, int s, int d, int& rez)
{
	int** rg = new int* [v];
	for (int i = 0; i < v; ++i)
		rg[i] = new int[v];

	int* h = new int[v];
	int* e = new int[v];

	for (int i = 0; i < v; ++i)
		for (int j = 0; j < v; ++j)
			rg[i][j] = g[i][j];

	initializare_preflux(g, rg, v, s, d, h, e);

	bool continua = 0;
	while (1)
	{
		/*cout << '\n';
		for (int i = 0; i < v; ++i)
		{
			for (int j = 0; j < v; ++j)
				cout << rg[i][j] << ' ';
			cout << '\n';
		}

		cout << "excesuri:\n";
		for (int i = 0; i < v; ++i)
			cout << e[i] << ' ';

		cout << "\ninaltimi:\n";
		for (int i = 0; i < v; ++i)
			cout << h[i] << ' ';
		cout << '\n';*/

		continua = 0;
		for (int i = 1; i < v - 1; ++i)
		{
			if (e[i] > 0)
			{
				bool exista_mai_mic = 0;
				for (int j = 0; j < v; ++j)
				{
					if (i != j && rg[i][j] > 0)
					{
						if (h[i] > h[j])
							exista_mai_mic = 1;
						if (h[i] == h[j] + 1)
						{
							pompare(rg, e, i, j);
							continua = 1;
							break;
						}
					}
				}
				if (continua)
					break;
				if (!exista_mai_mic)
				{
					inaltare(rg, h, v, i);
					continua = 1;
					break;
				}
			}
		}
		if (continua) continue;
		break;
	}
	//cout << e[d] << '\n';
	rez = e[d];
	delete[] h;
	delete[] e;
	distruge_graf(rg, v);
}


int main()
{
	ifstream fin("pompare.txt");
	int v, m, x, y, c;
	fin >> v >> m;

	int** g = new int* [v];
	for (int i = 0; i < v; ++i)
		g[i] = new int[v];

	init_graf(g, v);

	for (int i = 1; i <= m; ++i)
	{
		fin >> x >> y >> c;
		g[x][y] = c;
	}
	int rez = 0;
	pompare_preflux(g, v, 0, v - 1, rez);
	cout << rez;

	distruge_graf(g, v);
	return 0;
}
