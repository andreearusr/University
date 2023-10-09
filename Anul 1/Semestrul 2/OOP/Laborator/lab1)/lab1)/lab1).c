// lab1).c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nr, a, sum = 0;

    printf("Cate numere doriti sa introduecti? ");
    scanf_s("%d", &nr);

    for (int i = 0; i < nr; i++)
    {
        scanf_s("%d", &a);
        sum = sum + a;

    }

    printf("Suma numerelor este %d", sum);

    return 0;
}