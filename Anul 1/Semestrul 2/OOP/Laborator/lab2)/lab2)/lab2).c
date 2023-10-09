// lab2).c : pb 3)Determinati toate reprezentarile posibile ale unui numar natural ca suma de numere naturale consecutive
//

#include <stdio.h>


void calculeaza(unsigned nr)
/* functie care afiseaza un numar natural ca suma de numere naturale consecutive
* preconditii:  nr - numar natural dat de la utilizator
* postconditii: numarul este scris ca suma de numere naturale consecutive
*               sum - suma de numere naturale
*/
{
    unsigned sum = 0;
    unsigned i, j, k;
    for (i = 1; i<= nr/2; i++)
    {
        sum = i;
        for (j = i + 1; j<=nr; j++)
        { 
            sum = sum + j;
            if (sum >=nr)
                break;
        }
     
        if (sum == nr)
        {
            printf("%u= ", nr);
            for (k = i; k <= j; k++)
                printf("%u+", k);
            printf("\n");
        }
    }  
}

void meniu()
/* functie cu ajutorul careia afisam meniul problemei si gestionam optiunile utilizatorului
*/
{
    unsigned opt, nr;
    printf("\tMeniu:\n1. Numar natural reprezentat ca suma de numere naturale consecutive\n2. Iesire\n");
    printf("Alegeti optiunea: ");
    scanf_s("%u", &opt);
    if (opt == 1)
    {
        printf("Dati numarul natural: ");
        scanf_s("%u", &nr);
        calculeaza(nr);
        meniu();
    }
    else if (opt == 2)
    {
        printf("Goodbye!");
        return;
    }
    else
    {
        printf("Optiune invalida!\n");
        meniu();
    }

}

int main()
 /* functia principala main
 */
{
    meniu();
    return 0;
}

