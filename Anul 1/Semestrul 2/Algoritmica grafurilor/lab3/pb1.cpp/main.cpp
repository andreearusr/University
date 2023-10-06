#include <iostream>
#include <fstream>
using namespace std;

ifstream f("1.txt");

int s,x,y,po,i,j,n,m,u,v,k,inf=10000,nod, d_m;
int l[101],p[101], Q[101], S[101], w[101][101];


void initializare(int s, int n)
{
    for(i=0; i<n; i++)
    {
        p[i]=0;
        l[i]=inf;
    }

    l[s]=0;

}

void relax(int u, int v)
{
    if(l[v]>l[u]+w[u][v])
    {
        l[v]=l[u]+w[u][v];
        p[v]=u;

    }
}

int extract_minim(int &d, int n)
{
    d_m = inf;
    k=-1;
    m=n+1;
    for(i=0; i<d; i++)
    {
        nod=Q[i];
        if(l[nod] < d_m)
        {
            d_m = l[nod];
            m = nod;
            k=i;
        }
    }

    for(i=k; i<d-1; i++)
        Q[i]=Q[i+1];
    Q[d-1]=0;
    d--;
    return m;
}




void dijkstra(int s, int n)
{
    initializare(s,n);
    for(i=0; i<n; i++)
    {
        Q[i]=i;
    }
    int d=n;

    while(d!=0)
    {
        u=extract_minim(d,n);
        for(i=0; i<n; i++)
            if (w[u][i]!=0)
                relax(u,i);
    }
}


int main()
{

    f>>n>>m;
    while(f>>x>>y>>po)
        w[x][y]=po;

    cout<<"sursa: ";
    cin>>s;
    dijkstra(s,n);

    cout<<"costurile:\n";
    for(i=0; i<n; i++)
    {
        cout<<"de la "<<s<<" la "<<i<<": "<<l[i]<<"\n";

    }
    for(i=0; i<n; i++)
    {
      cout<<"par:"<<p[i]<<"\n";
    }
  return 0;
}
