#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("colorare.txt");
ofstream fout("rez.txt");


bool sigur(int A[100][100], int color[100], int c, int v)
{
    //verificam daca vreun varf vecin lui v are culoarea c
    for(int i=0; i<v; i++)
    {
       if(A[v][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

bool colorare_b(int A[100][100], int color[100], int k, int v, int V)
{
    if(v == V)  //cand am ajuns la o colorare a tuturor varfurilor, ne oprim
        return true;

    for(int c=0; c<k; c++)
    {
        if(sigur(A, color, c, v))   //verific cu ce culoare e sigur varful v
        {
            color[v] = c;
            if(colorare_b(A, color, k, v+1, V)==true)
                return true;
        }
    }
    return false;
}

///abordare backtracking
int main()
{
    int V,E,x,y;
    int A[100][100], color[100];

    fin>>V>>E;  //V-nr varfuri  E-nr muchii

    for(int i=0; i<V; i++)
        color[i]=0;  //initializam culoarea fiecarui varf cu 0

    while(fin>>x>>y){
        A[x][y]=A[y][x]=1;  //construim matricea de adiacenta
    }

    for(int k=1; k<INT_MAX; k++)  //k-numarul de culori
    {
       bool ok = colorare_b(A, color, k, 0, V);
       if(ok==true)
       {
            fout<<k<<"\n";
            for(int i=0; i<V; i++)
                fout<<color[i]<<" ";
            break;
       }
        else
            continue;
    }

    return 0;

}
