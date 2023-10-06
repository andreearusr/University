#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

ifstream fin("studenti.txt");
ofstream fout("rez.txt");


bool BFS(int G[100][100],int V, int s, int d, int parent[]){

    bool* viz=new bool[V];

    for(int i=0; i<V; i++)
        viz[i]=false;

    queue<int> Q;
    Q.push(s);
    parent[s]=-1;
    viz[s]=true;

    while(!Q.empty())
    {
        int u = Q.front();  //luam primul element din coada
        Q.pop();

        for(int v=0; v<V; v++){
            if(viz[v]==false && G[u][v]!=0)
            {
                Q.push(v);  //insereaza v in coada
                parent[v]=u;
                viz[v]=true;
            }
        }
    }

    if(viz[d]==true)
    {
        delete[] viz;
        return true;
    }

    delete[] viz;
    return false;

}


int Ford_Fulkerson(int rG[100][100], int G[100][100], int& V, int s, int d){

    int u, v;
    //initializare graf rezidual
    for(u=0; u < V; u++)
        for(v=0; v < V; v++)
            rG[u][v]= G[u][v];

    int parent[V];
    int fluxM=0;

    while(BFS(rG, V, s, d, parent))
    {
        int fluxC = INT_MAX;
        for(v=d; v!=s; v=parent[v])
        {
            u = parent[v];
            fluxC = min(fluxC, rG[u][v]);
        }

        for(v=d; v!=s; v=parent[v])
        {
            u = parent[v];
            rG[u][v]-= fluxC;
            rG[v][u]+= fluxC;

        }

        fluxM += fluxC;  //crestem valoarea fluxului cat timp gasim un drum rezidual

    }
    return fluxM;

}


int main()
{
    ///N- nr de cladiri(camine + clad oras + clad centrale)
    ///C- nr de camine
    ///D- nr de drumuri
    ///camine (0 -- C-1)
    ///clad oras (C -- N-2)
    ///clad centrala (N-1)

    int N,C,D,m,x,y;
    int G[100][100],rG[100][100];

    fin>>N>>C>>D;
    for(int i=0; i<D; i++)
    {
        fin>>x>>y>>m;
        G[x][y]=m;
    }

    int s=N;  //adaug un nou varf supersursa in graf
    for(int i=0; i<C; i++)
        G[s][i]=INT_MAX;  //trimit spre camine fluxul infinit

    int fluxS=0;
    int flux;

    int V=N+1;
    flux = Ford_Fulkerson(rG,G,V,s,N-1);  //apelez FF pe noul graf  rG-graf rezidual, G-graful, V-nr de varfuri, s-sursa, N-1-destinatia
    fout<<flux<<" \n";  //numar maxim studenti ce pot ajunge simultan la facultate

    for(int i=0; i<C; i++)
    {
        int SrG=0;
        int SG=0;
        for(int j=0; j<N; j++)
        {
            SrG+=rG[i][j]; //suma ponderilor din graful rezidual de la varful i la celelalte varfuri
            SG+=G[i][j]; //suma ponderilor din graful initial de la varful i la celelalte varfuri
        }
        fout<<SG-SrG<<" ";
    }

    return 0;
}
