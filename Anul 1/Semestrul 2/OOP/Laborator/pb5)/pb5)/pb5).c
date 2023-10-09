// pb5).c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

int este_prim(int nr)
{
    int ok = 1;
    for (int i = 2; i <= nr / 2; i++)
    {
        if (nr % i == 0)
        {
            ok=0;
        }
    }
    return ok;
}
void tipareste(int n)
{
    int i;
    for(i=1; i<=n; i++)
    {
        if (este_prim(i) == 1)
        {
            for (int j = i; j >= 1; j--)
                printf("%d,", j);
        }
        if (este_prim(i) == 0)
        {
            for (int j = 2; j <= n/2; j++)
            {
                if (i % j == 0)
                    printf("%d,", i);
                    for(int z=1; z<=j; z++)
                        printf("%d,", j);
            }
        }

    }

}

int main()
{
    int n;
    printf("dati n:");
    scanf_s("%d", &n);
    tipareste(n);
    return 0;
}

