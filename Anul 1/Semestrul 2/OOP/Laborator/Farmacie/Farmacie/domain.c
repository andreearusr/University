
#define _CRT_SECURE_NO_WARNINGS

#include "domain.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

Medicine create_medicine(int code, char* name, float concentration, int quantity)
{
	Medicine med;
	med.code = code;
	med.name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy_s(med.name, strlen(name) + 1, name);
	med.concentration = concentration;
	med.quantity = quantity;

	return med;
}

Medicine copyMed(Medicine* med)
{
	return create_medicine(med->code, med->name, med->concentration, med->quantity);
}
void destroy_med(Medicine* med)
{
	free(med->name);
	med->name = NULL;
	med->code = -1;
	med->concentration = -1;
	med->quantity = -1;
}

int validate_med(Medicine med)
{
	if (med.code < 0)
		return 1;
	
	if (strlen(med.name) == 0)
		return 2;

	if (med.concentration < 0 || med.concentration > 100)
		return 3;
	
	if (med.quantity < 0)
		return 4;
	
	return 0;

}


void test_domain()
{
	Medicine med = create_medicine(12, "Nurofen", 34.5, 7);
	assert(med.code == 12);
	assert(strcmp(med.name, "Nurofen") == 0);
	assert(med.concentration == 34.5);
	assert(med.quantity == 7);


	Medicine med2 = copyMed(&med);
	assert(med2.code == 12);
	assert(strcmp(med2.name, "Nurofen") == 0);
	assert(med2.concentration == 34.5);
	assert(med2.quantity == 7);
	destroy_med(&med);
	destroy_med(&med2);

	assert(med.name == NULL);
	assert(med.code == -1);
	assert(med.concentration == -1);
	assert(med.quantity == -1);
	assert(med2.name == NULL);
	assert(med2.code == -1);
	assert(med2.concentration == -1);
	assert(med2.quantity == -1);

}