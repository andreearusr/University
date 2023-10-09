#pragma once

#include "repo.h"

/*
a MedStore type structure which contains: -> a Repository structure type
*/
typedef struct {
	Repository allMed;
} MedStore;


/*
Create a MedStore (a store of all medicines)
pre: -
post: return a store  
*/
MedStore createMedStore();


/*
Destroy the store of medicines
pre: MedStore* store - adress of the structure of type MedStore
post: memory is released
*/
void destroyStore(MedStore* store);


/*
Add a medicine to the store
pre: MedStore* store - adress of the structure of type MedStore
	 int code - the code of a medicine
	 char* name - string adress -> name of the medicine
	 float concentration - the concentration for a medicine 
	 int quantity - the quantity of a medicine in the store
post: return 0 if the medicine is valid and added with succes in the store
	  return !=0 if the medicine is invalid 
*/
int add_medicine(MedStore* store, int code, char* name, float concantration, int quantity); 


/*
Take all medicines in the store
pre: MedStore* store - adress of the structure of type MedStore
post: return all medicines from the store in a repository
*/
Repository getallMed(MedStore* store);


/*
pre: MedStore* store - adress of the structure of type MedStore
	 int code - the code of a medicine
post: return 1 if the medicine is in the store
	  return 0 if the medicine is not in the store
*/
int find_m(MedStore* store, int code);



/*
Updates the quantity of a medicine from store
pre: MedStore* store - adress of the structure of type MedStore
	 int code - the code of a medicine
	 int quantity - the quantity for a medicine
post: the final quantity of element grows with quantity
*/
void update_quantity(MedStore* store, int code, int quantity);



/*
Empties a stock of a medicine from store
pre: MedStore* store - adress of the structure of type MedStore
	 int code - the code of the medicine
post: quantity of the medicine(if found) = 0
*/
void delete_medicine(MedStore* store, int code);


/*
Modify an medicine(if found) from store   medicine.name <- name
										  medicine.concentration <- concentration
pre: MedStore* store - adress of the structure of type MedStore
	 int code - the code of the medicine
	 char* name - string adress -> name for a medicine
	 float concentration - the concentration for a medicine
post: the medicine(if found), is updated with a new name and a new concentration
*/
void update_medicine(MedStore* store, int code, char* name, float concentration);


/*
Sort the medicines from the stock according to the chosen options -> name -> opt1==1 ascending order
																		  -> opt1==2 descending order
																  
pre: MedStore* store - adress of the structure of type MedStore
	 int opt1 - the option you want to sort by
post: return a repository with sorted medicines
*/
Repository sort_name(MedStore* store, int opt1);


/*
Sort the medicines from the stock according to the chosen options -> quantity -> opt1==1 ascending order
																		      -> opt1==2 descending order

pre: MedStore* store - adress of the structure of type MedStore
	 int opt1 - the option you want to sort by
post: return a repository with sorted medicines
*/
Repository sort_quantity(MedStore* store, int opt1);


/*
Sort the medicines from the stock according to the chosen options -> quantity --> medicines with quantity < quantity																	 
pre: MedStore* store - adress of the structure of type MedStore
	 int quantity - the option you want to sort by
post: return a repository with filtered medicines
*/
Repository filter_quantity(MedStore* store, int quantity);


/*
Sort the medicines from the stock according to the chosen options -> name --> medicines with first leter of name = lit
pre: MedStore* store - adress of the structure of type MedStore
	 char lit - the option you want to sort by
post: return a repository with filtered medicines
*/
Repository filter_name(MedStore* store, char lit);


/*
Verify if everything goes right in service
*/
void test_service();

/*
Verify if everything goes right in service (sort the medicines)
*/
void test_sort();


/*
Verify if everything goes right in service (filter the medicines)
*/
void test_filter();

/*
Verify if everything goes right in service (update medicine)
*/
void test_update();
