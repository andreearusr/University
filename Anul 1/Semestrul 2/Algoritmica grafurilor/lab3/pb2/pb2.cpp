#include <iostream>
#include <fstream>
using namespace std;

ifstream f("2.txt");

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


bool bellman_ford(int s, int n)
{
    initializare(s,n);
    for(int i=1; i<n-1; i++)
        for(int u=0; u<n; u++)
            for(int v=0; v<n; v++)
                if(w[u][v]!=0)
                    relax(u,v);

    for(int u=0; u<n; u++)
        for(int v=0; v<n; v++)
            if(w[u][v]!=0 && l[v]>l[u]+w[u][v])
                return false;
    return true;
}


int main()
{

    f>>n>>m>>po;
    while(f>>x>>y>>po)
        w[x][y]=po;

    cout<<"sursa: ";
    cin>>s;
    bool r = bellman_ford(s,n);

    if(r==false)
    {
        cout<< "Nu avem solutie\n";
    }
    else
    {
    cout<<"costurile:\n";
    for(i=0; i<n; i++)
        cout<<l[i]<<" ";
    }
    cout<<"\n";
    for(i=0; i<n; i++){
        cout<<p[i]<<" ";
    }
  return 0;
}

