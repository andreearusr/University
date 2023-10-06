#include <iostream>
#include <fstream>

using namespace std;
ifstream f("graf3.txt");
int t[100][100],n,i,j,k;

void matricea_inchiderii_tranz()
{
    f>>n;
    for (i = 1; i <= n; i++)
        for (j=1; j<=n; j++)
        {
            f>>t[i][j];
        }

    for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (t[i][j] == 0)
					t[i][j] = (t[i][k] && t[k][j]);

}

void afisare()
{
    cout<<"Matricea inchiderii tranzitive:\n";
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<t[i][j]<<" ";
        cout<<"\n";
    }

}
int main()
{
    matricea_inchiderii_tranz();
    afisare();

    f.close();
    return 0;
}
