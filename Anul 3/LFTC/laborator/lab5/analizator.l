%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analizator.tab.h"




typedef struct Node
{
   char atom[257];
   int pozitie;
   struct Node *next;
}Noden;

typedef struct {
    char token[257];
    int symbolTableCode;
}PIF;

typedef struct{
    char token[257];
    int index;
}ST;

ST SymbolTableID[100];
ST SymbolTableCONST[100];
int stLengthID = 0;
int stLengthCONST = 0;

PIF ProgramInternalForm[300];
int pifLength = 0;

int errorFound = 0;
int lineNumber = -1;
int pozID=0,pozCONST=0;

void push( Noden** head, int node_data,char* atom)
{
    Noden* newNode = (Noden*)malloc(sizeof(Noden));

    newNode->pozitie = node_data;

    strcpy(newNode->atom ,atom);

    newNode->next = (*head);

    (*head) = newNode;
}

void insertAfter( Noden* prev_node, int node_data,char* atom)
{
if (prev_node == NULL)
{
   return;  }
 
   Noden* newNode =(Noden*)malloc(sizeof( Noden));
   newNode->pozitie = node_data;

   strcpy(newNode->atom,atom);

   newNode->next = prev_node->next;
 
    prev_node->next = newNode;
}



/* insert new node at the end of the linked list */
void append(Noden** head, int node_data,char* cuvant)
{
    Noden* newNode = (Noden*)malloc(sizeof(Noden));

    struct Node* last = *head; 

    newNode->pozitie = node_data;
    strcpy(newNode->atom ,cuvant);

    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
}
Noden* headIDprec = NULL;
Noden* headCONSTprec = NULL;

void afisare() {
    
    printf( "\nFIP:\nCOD ATOM  |  Pozitie in TS\n");
    
    for(int i = 0; i < pifLength; i++) {
    
        printf(" %s  %d ", ProgramInternalForm[i].token, ProgramInternalForm[i].symbolTableCode);
        printf("\n");
    }
    
    printf("~~~~~~~ End PIF ~~~~~~~\n");
    printf("\n");
    printf("TS ID:\nPOZITIE  |  SIMBOL  |  LEGATURA_POZ\n");
    while(headIDprec != NULL) {
        if(headIDprec->next!=NULL)
             printf("%d %s  %d\n",headIDprec->pozitie,headIDprec->atom,headIDprec->next->pozitie);
        else
            printf("%d %s  %d\n",headIDprec->pozitie,headIDprec->atom,-1);
        headIDprec = headIDprec->next;
    }
    printf("TS CONST:\nPOZITIE  |  SIMBOL  |  LEGATURA_POZ\n");

    while (headCONSTprec != NULL) {
        if (headCONSTprec->next != NULL)
            printf("%d %s  %d\n",headCONSTprec->pozitie,headCONSTprec->atom,headCONSTprec->next->pozitie);
        else
            printf("%d %s  %d\n",headCONSTprec->pozitie,headCONSTprec->atom,-1);
        headCONSTprec = headCONSTprec->next;
    }
}



int addToSTID(char* cuvant ) {
    Noden* tsIDprec = headIDprec;
	Noden* tsCONSTprec = headCONSTprec;
	int atominserted = 0;
		if (headIDprec == NULL) //lista e goala
		{
			append(&headIDprec, pozID+1, cuvant);
			pozID++;
			tsIDprec = headIDprec;
			atominserted = 1;
		}
		struct Node* node = NULL; int pozz=0;
		while(tsIDprec!=NULL){
			char* atPrec=(char*)malloc(sizeof(tsIDprec->atom));
			atPrec=tsIDprec->atom;
			if (strcmp(cuvant, atPrec) > 0)
			{
				node = tsIDprec;
				atominserted = 1;
			}
			if (strcmp(cuvant, atPrec) == 0)
			{
				atominserted = 2;
				pozz = tsIDprec->pozitie;
			}
			if (tsIDprec->next != NULL)
				tsIDprec = tsIDprec->next;
			else break;
		}
		
		if (atominserted == 0)
		{
			push(&headIDprec, pozID+1,cuvant);
			pozID++;
		}
		if(atominserted==1)
			{insertAfter(node, pozID+1, cuvant);pozID++;}
		if (pozz != 0)
			return pozz;
		else
			return pozID;
	
	
}

int addToSTCONST(char* cuvant) {
	Noden* tsIDprec = headIDprec;
	Noden* tsCONSTprec = headCONSTprec;
	int atominserted = 0;
	if (headCONSTprec == NULL) //lista e goala
                {
                    append(&headCONSTprec, pozCONST+1, cuvant);
					pozCONST++;
                    tsCONSTprec = headCONSTprec;
                    atominserted = 1;
                }
                struct Node* node = NULL; int pozz = 0;
                while (tsCONSTprec != NULL) { //parcurg lista inlantuita
                    char* atPrec=(char*)malloc(sizeof(tsCONSTprec->atom));
					atPrec = tsCONSTprec->atom;
                    if (strcmp(cuvant, atPrec) > 0)
                    {
                        node = tsCONSTprec;//memorez elementul dupa care sa memorez lexicografic cuv nou
                        atominserted = 1;
                    }
                    if (strcmp(cuvant, atPrec) == 0) //nu adaug in ts un element deja existent
                    {
                        atominserted = 2;
                        pozz = tsCONSTprec->pozitie;
                    }
                    if (tsCONSTprec->next != NULL)
                        tsCONSTprec = tsCONSTprec->next;
                    else break;
                }

                if (atominserted == 0)
                {
                    push(&headCONSTprec, pozCONST+1, cuvant); //pun la inceputul listei un element neadaugat
					pozCONST++;
                }
                if (atominserted == 1)
                    {insertAfter(node, pozCONST+1, cuvant); //adaug dupa un element
					pozCONST++;
						}
                if (pozz != 0)
                    return pozz;
                else
                    return pozCONST;
}

void addToPIF(char* token, int stCode) {
	strcpy(ProgramInternalForm[pifLength].token, token);
	ProgramInternalForm[pifLength].symbolTableCode = stCode;
	
	pifLength++;
}
%}

digit				[0-9]
octal_digit			[0-7]
ndigit				[1-9]
hex_digit			[0-9a-fA-F]
hex_prefix			0[xX]	

digit_sequence		{digit}+
decimal_exponent	[eE][+-]?{digit_sequence}
suffix				[fF]

int_const		({ndigit}{digit}*)|(0{octal_digit}*)|({hex_prefix}{hex_digit}+)|(0[bB][01]+)
float_const  	({digit}+{decimal_exponent}{suffix}?)|({digit_sequence}\.{decimal_exponent}?{suffix}?)|({digit_sequence}?\.{digit_sequence}{decimal_exponent}?{suffix}?)


REAL_NUMBER  ({int_const}|{float_const})
IDENTIFIER   [a-zA-Z][a-zA-Z0-9_]*
STRING       \".*\"

%%

int														{addToPIF(yytext, 2);return INT;}
double													{addToPIF(yytext, 3);return DOUBLE;}
main													{addToPIF(yytext, 9);return MAIN;}
if														{addToPIF(yytext, 6);return IF;}
else													{addToPIF(yytext, 7);return ELSE;}
for														{addToPIF(yytext, 8);return FOR;}
cin>>													{addToPIF(yytext, 4);return CIN;}
cout<<													{addToPIF(yytext, 5);return COUT;}
cattimp							     					{ addToPIF(yytext, 37); return CATTIMP;}
sfcattimp							    				{ addToPIF(yytext, 38); return SFCATTIMP;}
executa     											{ addToPIF(yytext, 39); return EXECUTA;}


&&														{addToPIF(yytext, 28); return AND;}
\|\|													{addToPIF(yytext, 29); return OR;}
>=														{addToPIF(yytext, 16);return GE;}
\<=														{addToPIF(yytext, 15);return LE;}
==														{addToPIF(yytext, 12);return EQUAL;}

","														{addToPIF(yytext, 26);return ',';}
";"														{addToPIF(yytext, 36);return ';';} 
"("														{addToPIF(yytext, 22);return '(';}
")"														{addToPIF(yytext, 23);return ')';}
"{"														{addToPIF(yytext, 24);return '{';}
"}" 													{addToPIF(yytext, 25);return '}';}
"="														{addToPIF(yytext, 11);return '=';}
"-"														{addToPIF(yytext, 21);return '-';}
\*														{addToPIF(yytext, 17);return '*';}
\+														{addToPIF(yytext, 20);return '+';}
\/														{addToPIF(yytext, 18);return '/';}
"%"														{addToPIF(yytext, 19);return '%';}
"<"     												{addToPIF(yytext, 13);return '<';}
">"     												{addToPIF(yytext, 14);return '>';}

{REAL_NUMBER}                    						{int stCode = addToSTCONST(yytext); addToPIF(yytext, 0);return CONST;}
{IDENTIFIER}  											{int stCode = addToSTID(yytext); addToPIF(yytext, 1);return VAR;}
{STRING}												{int stCode = addToSTID(yytext); addToPIF(yytext, stCode); return VAR;}


[ \n\t]													;

.														;
%%

