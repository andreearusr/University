// lab2).c : pb2) Genereaza primele n (n natural dat) numere prime.
//

#include <stdio.h>

void nr_prime(unsigned n)
{
	int contor=0;
	int nr = 2;

	while (contor<n) 
	{
		int e_prim = 1;
		for (int i=2; i<=nr/2; i++)
		{
			if (nr % i == 0)
			{
				e_prim = 0;
				break;
			}
		}

		if (e_prim == 1)
		{
			printf("%d ", nr);
			contor++;
		}
		nr++;
	}
}

int main()
{
	unsigned n;
	printf("Dati numarul de numere prime pe care doriti sa il generati: ");
	scanf_s("%u", &n);
	nr_prime(n);
	return 0;
}

