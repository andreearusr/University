#pragma once

#include "service.h"

/*
Function with which we check if all goes right in domain, repository and service
*/
void run_all_tests();

/*
Function that manages user-given commands
*/
void run();


/*
Tries to add a medicine to the store
pre: MedStore* store - adress of the structure of type MedStore
post: a valid medicine is added to the store
	  warns the user if he entered wrong data
*/
void add_ui(MedStore* store);


/*
Show all items in the store
pre: MedStore* store - adress of the structure of type MedStore
post: list of items in the store
*/
void showall(MedStore* store);


/*
Tries to empty a stock of a medicine
pre: MedStore* store - adress of the structure of type MedStore
post: the stock of the wanted medicine is empty
	  warns the user if he entered wrong data
*/
void delete_ui(MedStore* store);


/*
Tries to update a medicine (medicine.name <- new_name, medicine.concentration <- new_concentration)
pre: MedStore* store - adress of the structure of type MedStore
post: the medicine(if found) is updated
	  warns the user if he entered wrong data
*/
void update_ui(MedStore* store); 


/*
Sort the medicines from the stock according to the chosen options
pre: MedStore* store - adress of the structure of type MedStore
post: Show medicines from the store, sorted
	  warns the user if he entered wrong data
*/
void sort_ui(MedStore* store);


/*
Filter the medicines from the stock according to the chosen options
pre: MedStore* store - adress of the structure of type MedStore
post: Show medicines from the store, filtered
	  warns the user if he entered wrong data
*/
void filter_ui(MedStore* store);


