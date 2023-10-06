#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fisier;
    int nr,a[20];
    int i=0;

    fisier = fopen("numere.txt","r");
    if (fisier == NULL)
    {
        perror("Eroare in deschiderea fisierului\n");
        return(-1);
    }

    {
        fscanf(fisier, "%d", &nr);
        scanf("%d",&a[i]);
    }while (i<6)

    for(int i=0;i<6;i++)
       printf("%d",a[i]);

return 0;
}
