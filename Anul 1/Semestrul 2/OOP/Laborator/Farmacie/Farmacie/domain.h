#pragma once

/*
a Medicine type structure which contains: -> a code (integer)
										  -> a name (string)
										  -> a concentration (float)
										  -> a quantity (integer)
*/
typedef struct {
	int code;
	char* name;
	float concentration;
	int quantity;
} Medicine;


/*
Return an object of type Medicine
pre:	int code - the code of a medicine
		char* name - string adress -> name of the medicine
		float concentration - the concentration for a medicine 
		int quantity - the quantity of a medicine in the store
post: the object of type Medicine is created 
*/
Medicine create_medicine(int code, char* name , float concentration, int quantity );


/*
Dealocate the memory occupied by a medicine
pre: Medicine* med - adress of the structure of type Medicine
post: memory is released
*/
void destroy_med(Medicine* med);


/*
Create a copy for a medicine
Copy all the sub-parts
pre: Medicine* med - adress of the structure of type Medicine
post: return a copy of a medicine
*/
Medicine copyMed(Medicine* med);


/*
Validate a medicine
pre: Medicine med - the desired medicine to be validated
post: return 0 if all the sub-parts of medicine are valid
	  return 1 if -> the code of medicine is less than 0 (integer)
	  return 2 if -> the name of medicine is empty (string)
	  return 3 if -> the concentration of medicine is less than 0 or bigger than 100 (float)
	  return 4 if -> the quantity of medicine is less than 0 (integer)

*/
int validate_med(Medicine med);



/*
Verify if everything goes right in domain
*/
void test_domain();



