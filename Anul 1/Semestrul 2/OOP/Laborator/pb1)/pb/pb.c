// pb1.c : Genereaza numere prime mai mici decat un numar natural dat.
//

#include <stdio.h>


int prim(int nr)
{
	int e_prim = 1;
	for (int i = 2; i <= nr/2; i++)
	{
		if (nr % i == 0)
			e_prim = 0;
	}
	return e_prim;
}

void nr_prime(int nr)
{
	int ok;
	if (nr == 1) printf("Nu exista numere prime mai mici decat 1!");
	if (nr == 2) printf("1");
	if (nr == 3) printf("1 2");
	if (nr > 3)
	{
		for (int i = 1; i < nr; i++)
		{
			ok = prim(i);
			if (ok == 1) printf("%d ",i);
		}
	}
}

int main()
{
	int nr;
	printf("Dati un numar:");
	scanf_s("%u", &nr);
	nr_prime(nr);

	return 0;
}

