
#include <iostream>
#include <fstream>

using namespace std;
ifstream f("3.txt");

int inf=100000;
int n,m,s,l,costuri[100][100], costuri_noi[100][100], newM[100][100], newC[100][100];
int d[100],d_noua[100], h[100], p[100], Q[100];


void initializare(int s, int n)
{
    for(int i=0; i<n; i++)
    {
        p[i]=0;
        d[i]=inf;
    }

    d[s]=0;

}

void relax(int u, int v)
{
    if(d[v]>d[u]+costuri[u][v])
    {
        d[v]=d[u]+costuri[u][v];
        p[v]=u;
    }

}

int extract_minim(int &l, int n)
{
    int d_m = inf;
    int k=-1;
    m=n+1;
    for(int i=0; i<l; i++)
    {
        int nod=Q[i];
        if(d_noua[nod] < d_m)
        {
            d_m = d_noua[nod];
            m = nod;
            k=i;
        }
    }

    for(int i=k; i<l-1; i++)
        Q[i]=Q[i+1];
    Q[l-1]=0;
    l--;
    return m;
}


bool bellman_ford(int s, int n)
{
    initializare(s,n);
    for(int i=1; i<n-1; i++)
        for(int u=0; u<n; u++)
            for(int v=0; v<n; v++)
                if(costuri[u][v]!=0)
                    relax(u,v);

    for(int u=0; u<n; u++)
        for(int v=0; v<n; v++)
            if(costuri[u][v]!=0 && d[v]>d[u]+costuri[u][v])
                return false;
    return true;
}

void dijkstra(int s, int n)
{
    for(int i=0; i<n; i++)
    {
        p[i]=0;
        d_noua[i]=inf;
    }

    d_noua[s]=0;

    for(int i=0; i<n; i++)
        Q[i]=i;
    int k=n;

    while(k!=0)
    {
        int u=extract_minim(k,n);
        for(int v=0; v<n; v++)
            if (costuri[u][v]!=0){
                if(d_noua[v] > d_noua[u] + costuri_noi[u][v]){
                d_noua[v] = d_noua[u] + costuri_noi[u][v];
                p[v]=u;
                }
            }
    }
}


void johnson(int n)
{
    int newN=n+1;

    for(int i=0; i<n; i++)
    {
         costuri_noi[newN][i]=0;
         d_noua[i]=1;
    }


    if (bellman_ford(n, newN) == false)
    {
        cout<<"-1 ";
        return;
    }
    else
    {
        for(int i=0; i<newN; i++)
            h[i] = d[i];

        for(int i=0; i<newN; i++)
            for(int j=0; j<newN; j++)
                costuri_noi[i][j] = costuri[i][j] + h[i] - h[j];

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if(i!=j && costuri[i][j]!=0)
                    cout<<i<<" "<<j<<" "<<costuri_noi[i][j]<<"\n";

        for(int i=0; i<n; i++)
        {
            dijkstra(i,n);
            for(int j=0; j<n; j++)
                if(d_noua[j]==inf)
                    cout<<"inf ";
                else
                    cout<<d_noua[j] - h[i] + h[j]<<" ";
            cout<<"\n";
        }

    }

}


int main()
{
    int x,y,po;
    f>>n>>m;
    while(f>>x>>y>>po)
    {
        costuri[x][y]=po;
    }

    johnson(n);

    return 0;
}
