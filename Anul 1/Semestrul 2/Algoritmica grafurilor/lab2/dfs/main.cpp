#include <iostream>
#include <fstream>

using namespace std;
int s,x,y,i,j,n,m, a[100][100], viz[100];
int nrcomp;
ifstream f("dfs.txt");

void citire()
{
    f>>n;
    while(f>>x>>y)
        a[x][y]=1;

}
/*
void dfs(int k)
{
    int i;
    viz[k]=1;
    for(i=1;i<=n;i++)
    {
        if (a[k][i]==1 && viz[i]==0)
        {
                cout<<i<<" ";
                dfs(i);
        }
    }
}

*/


void DFS(int x)
{ int i;
  viz[x]=nrcomp;
  for(i=1;i<=n;i++)
    if (a[x][i]==1 && viz[i]==0) DFS(i);
}


void ComponenteConexe()
{ int i;
  for(i=1;i<=n;i++)
    if (viz[i]==0) { nrcomp++; DFS(i);}
}


void AfisareComponenteConexe()
{ int i,j;
  for(i=1;i<=nrcomp;i++)
      { cout<<"Componenta "<<i<<": ";
        for(j=1;j<=n;j++)
            if (viz[j]==i) cout<<j<<" ";
        cout<<endl;
      }

}

int main()
{
    citire();
    //cin>>s;
    //cout<<s<<" ";
    //dfs(s);
    DFS(1);
    ComponenteConexe();
    AfisareComponenteConexe();
    cout<<nrcomp;
    return 0;
}
