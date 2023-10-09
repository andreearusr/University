#pragma once
#include "domain.h"

/*
a generic structure (ElemType) initialized with Medicine type structure
*/
typedef Medicine ElemType;


/*
a Repository type structure which contains: -> an adress which reffers a structure of ElemType 
										    -> a lg (length) (integer)
										    -> a capacity (integer)
										  
*/
typedef struct {
	ElemType* elems;
	int lg;
	int capacity;
} Repository;



/*
Create an empty list
pre: -
post: return an empty repository 
*/
Repository createRepo();


/*
Destroy list
pre: Repository* r - adress of the structure of type Repository
post: memory is released
*/
void destroyRepo(Repository* r);


/*
Get an element of type ElemType from the list
pre:  Repository* r - adress of the structure of type Repository
		poz - position of the element, need to be valid
post: return element on the given position
*/
ElemType get(Repository* r, int poz);


/*
Modify the element of type ElemType on the given pozition
pre:  Repository* r - adress of the structure of type Repository
	  poz - position of the element, need to be valid
	  Medicine med - a medicine
post: return the overwrited element
*/
ElemType set(Repository* r, int poz, Medicine med);


/*
pre: Repository* r - adress of the structure of type Repository
post: return the number of elements(type ElemType) in the list
*/
int len(Repository* r);


/*
Add an element of type ElemType into the list
pre: Repository* r - adress of the structure of type Repository
	 ElemType el - an element of type ElemType
post: element is added to the end of the list
*/
void add_repo(Repository* r, ElemType el);


/*
Make a copy of the list
pre:  Repository* r - adress of the structure of type Repository
post: return rez containing the same elements as r
*/
Repository copyRep(Repository* r);


/*
Check if an element is in the list(repository)
pre: Repository* r - adress of the structure of type Repository
	 int code - the code(unique) of the element
post: return 1 if the element is in the list
	  return 0 if the element is not in the list
*/
int find(Repository* r, int code);



/*
Modify an element(if found) from list of type ElemType   el.name <- name
														 el.concentration <- concentration
pre: Repository* r - adress of the structure of type Repository
	 int code - the code(unique) of the element
	 char* name - string adress -> name for an element
	 float concentration - the concentration for an element
post: the element(if found), is updated with a new name and a new concentration
*/
void update_repo(Repository* r, int code, char* name, float concentration);


/*
Updates the quantity of an element from list(repository)
pre: Repository* r - adress of the structure of type Repository
	 int code - the code of the element
	 int quantity - the quantity for an element
post: the final quantity of element grows with quantity
*/
void update_quantity_r(Repository* r, int code, int quantity);


/*
Verify if everything goes right in repository
*/
void test_repo();


/*
the type of the function for comparing 2 elements
returns 0 if they are equal, 1 if m1>m2, -1 otherwise
*/
typedef int(*FunctieComparare)(	Medicine* m1, Medicine* m2);


/*
if opt1==1 ascending order,  opt==2  descending order
cmpF - the relationship according to which the list is sorted 
*/
void sort(Repository* r, int opt1, FunctieComparare cmpF);

