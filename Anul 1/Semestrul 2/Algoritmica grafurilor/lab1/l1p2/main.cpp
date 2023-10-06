#include <iostream>
#include <fstream>

using namespace std;
ifstream f("graf2.txt");
int a[100][100],n, viz[100];
const int maxx=100000;


void vf_izolate()
{
    f>>n;
    cout<<"Varfurile izolate sunt: ";
    for (int i=1; i<=n; i++)
    {
        int Sum=0;
        for (int j=1; j<=n; j++)
        {
            f>>a[i][j];
            Sum=Sum+a[i][j];
        }
        if (Sum == 0)
            cout<<i<<" ";
    }
    cout<<"\n";
}

void gr_regular()
{
    int reg=1;
    int Sum1=0;
    int i=1;

    if (i==1)
    {
        for(int j=1;j<=n;j++)
        {
            f>>a[i][j];
            Sum1=Sum1+a[i][j];
        }
    }

    for (int i=2; i<=n; i++)
    {
        int Sum=0;
        for (int j=1; j<=n; j++)
        {
            f>>a[i][j];
            Sum=Sum+a[i][j];
        }
        if (Sum != Sum1)
            reg=0;
    }
    if (reg==1)
        cout<<"Graful este regular\n";
    else
        cout<<"Graful nu este regular\n";

}


void dfs(int k)
{
    int i;
    viz[k]=1;
    for(i=1;i<=n;i++)
    {
        if (a[k][i]==1 && viz[i]==0)
        {
                dfs(i);
        }
    }
}

int conex()
{
    int i;
    dfs(1);
    for (i=1;i<=n;i++)
        if (viz[i]==0)
        {
            return 0;
        }
    return 1;
}

void citire()
{
	int i,j;
	f >> n;

    for (i = 1; i <= n; i++)
        for (j=1; j<=n; j++)
        {
            f>>a[i][j];
        }

	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
            if (a[i][j]!=1)
                a[i][j] = a[j][i] = maxx;
}



void rf()
{
	int i, j, k;
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (i != j)
					if (a[i][j]>a[i][k] + a[k][j])
						a[i][j] = a[i][k] + a[k][j];
}

void afis()
{
    cout<< "\tMatricea distantelor:\n";
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			if (a[i][j] != maxx) cout << a[i][j] <<" ";
			else cout <<"inf ";
			cout <<"\n";
	}
}


int main()
{
    vf_izolate();
    gr_regular();

    if (conex()==1)
        cout<<"Graful este CONEX\n";
    else
        cout<<"Graful este neCONEX\n";

    citire();
    rf();
    afis();

    f.close();
    return 0;
}
