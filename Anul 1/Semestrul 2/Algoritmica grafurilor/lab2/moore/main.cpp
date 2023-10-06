#include <iostream>
#include <fstream>
using namespace std;

int s,x,y,i,j,n,m,v,k;
int a[100][100],l[100],Q[101],p[101],inf=10000,drum[100];
ifstream f("moore.txt");

void moore(int s, int n)
{
    int inc=0;
    for(i=1; i<=n; i++)
        l[i]=inf;
    l[s]=0;
    Q[inc]=s;
    inc++;
    while(inc != 0)
    {
        x=Q[0];
        for(i=0; i<inc-1; i++)
            Q[i]=Q[i+1];

        Q[inc-1]=0;
        inc--;
        for(y=1; y<=n; y++)
            if(a[x][y]==1)
                if (l[y]==inf)
                {
                    p[y]=x;
                    l[y]=l[x]+1;
                    Q[inc]=y;
                    inc++;
                }
    }
}

void drum_m(int v)
{
    k=l[v];
    drum[k]=v;
    while(k!=0)
    {
        drum[k-1]=p[drum[k]];
        k--;
    }
}


int main()
{
    cout<<"sursa: ";
    cin>>s;

    f>>n;
    while(f>>x>>y)
        a[x][y]=1;

    for(i=1; i<=n; i++)
        cout<<i<<" ";
    cout<<"\n";
    moore(s,n);

    for(i=1; i<=n; i++)
        if(l[i]==inf)
            cout<<"inf ";
        else
            cout<<l[i]<<" ";

    cout<<"\ndestinatie: ";
    cin>>v;

    drum_m(v);
    cout<<"Drumul de la "<<s<<" la "<<v<<": ";
    for(i=0; i<=l[v]; i++)
        cout<<drum[i]<<" ";
    cout<<"\n";

    return 0;
}
