#include <iostream>
#include <fstream>

using namespace std;
ifstream f("bfs.txt");
int n,m,s,x,y,i,j,a[100][100],viz[100];
int p,u,c[100];

void bfs(int s)
{
    for(i=1; i<=n; i++)
    {
        viz[i] = 0;
        c[i] = 0;
    }

    p=u=1;
    c[u]=s;
    viz[s]=1;
    while(p <= u)
    {
        for(i=1;i<=n;i++)
        {
        if(a[c[p]][i] != 0 && viz[i] == 0)
            {

            u++;
            c[u]=i;
            viz[i]=1;
            cout<<"\ndist fata de "<<i<<" este "<<u-1;
            }
        }
        p++;
    }

   cout<<"\n";
   for(i=1; i<=n; i++)
        cout<<c[i]<<" ";

}

int main()
{
    f>>n>>m;
    for(i=1;i<=n;i++)
    {
        f>>x>>y;
        a[x][y]=a[y][x]=1;
    }

    cout<<"Dati varful sursa: ";
    cin>>s;
    bfs(s);

    return 0;
}
