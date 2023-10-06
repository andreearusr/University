#include <iostream>
#include<stdio.h>
#include<fstream>
#include<algorithm>
using namespace std;

/*ifstream fin("in.txt");
ofstream fout("out.txt");*/

int main(int argc, char*argv[])
{
    char txtIN[20],txtOUT[20];
    cin>>txtIN;
    cin>>txtOUT;

    ifstream fin(txtIN);
   // ofstream fout(argv[2]);


    return 0;
}
