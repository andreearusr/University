#include <iostream>
#include <fstream>

using namespace std;
ifstream f("graf.txt");
int a[100][100],n,m;
int b[100][100];

void citire()
{
    int x,y;
    f >> n >> m;
    for (int i=1;i<=m;i++)
        {
            f >> x >> y;
            a[x][y]=1;
            a[y][x]=1;
            b[x][i]=1;
            b[y][i]=1;
        }
}

void matrice_adiacenta()
{
    cout<<"Matricea de adiacenta este:\n";
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout<<a[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

void matrice_incidenta()
{
    cout<<"Matricea de incidenta este:\n";
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
            cout<<b[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";

}

void liste_adiacenti()
{
    for (int i=1; i<=n; i++)
    {
        cout<<"Varful "<<i<<" are vecinii: ";
        for (int j=1; j<=n; j++)
            {
            if (a[i][j]==1)
                cout<<j<<",";
            }
        cout<<"\n";
    }
}


int main()
{
    citire();
    matrice_adiacenta();
    matrice_incidenta();
    liste_adiacenti();

    return 0;
}
