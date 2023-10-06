/*++
Se cere un program C care apeleaza functia sumaNumere scrisa in limbaj de asamblare. Aceasta functie primeste
ca parametri doua numere naturale citite in programul C, calculeaza suma lor si transmite aceasta valoare ca rezultat.
Programul C va afisa suma calculata de functia sumaNumere
--*/


#include <stdio.h>

// functia declarata in fisierul modulSumaNumere.asm
int sumaNumere(int a, int b);

int main()
{
    // declaram variabilele
    int a = 0;
    int b = 0;
    int sum = 0;

    // citim de la tastatura cele doua numere
    printf("a=");
    scanf("%d", &a);

    printf("b=");
    scanf("%d", &b);

    // apelam functia scrisa in limbaj de asamblare
    sum = sumaNumere(a, b);

    // afisam valoarea calculata de functie
    printf("Suma numerelor este %d", sum);
    return 0;
}
