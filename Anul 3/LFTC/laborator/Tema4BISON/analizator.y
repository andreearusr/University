%{
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1

%}

%error-verbose

%token INCLUDE
%token IOSTREAM
%token USING
%token NAMESPACE
%token STD
%token VAR
%token CONST
%token INT
%token DOUBLE
%token MAIN
%token IF
%token FOR
%token ELSE
%token CIN
%token COUT
%token AND
%token OR
%token GE
%token LE
%token EQ
%token DIF
%token WHILE
%token ENDL
%token IN
%token OUT

%%

P 	:	program										
	;

program	: lista_importuri INT MAIN '(' ')' '{' lista_instructiuni '}'	
		;
	
lista_importuri : import lista_importuri
				| import
				;

import : INCLUDE IOSTREAM
	   | USING NAMESPACE STD ';'
	   ;
		
lista_instructiuni	:	lista_ex lista_instructiuni														
					|	lista_ex											
					;

lista_ex	:	instructiune											
			|	declaratie											
			;

instructiune	:	IF '(' expresie ')' '{' lista_instructiuni '}' ELSE '{' lista_instructiuni '}'		
				|	IF '(' expresie ')' '{' lista_instructiuni '}'						
				|	FOR '(' expresii ';' expresii ';' expresii ')' '{' lista_instructiuni '}'	
				|	WHILE '(' expresie ')' '{' lista_instructiuni '}'				
				|	CIN	IN VAR ';'									
				|	COUT lista_afisari ';'									
				|	VAR '=' expresie ';'			
				;
		
lista_afisari	: afisare lista_afisari
				| afisare
				;
				
afisare 	: OUT STR
			| OUT ENDL
			;
				
expresii	:	expresie											
			|	CIN IN VAR											
			|	COUT lista_afisari											
			| 	VAR '=' expresie
			;

declaratie	:	tip lista_identificatori ';'															
			;

tip : INT
	| DOUBLE
	;

lista_identificatori 	: identificator ',' lista_identificatori
						| identificator
						;

identificator 	: identif
				;

identif		: VAR
			| VAR '=' CONST
			;

expresie	:	expresie AND expresie										
			|	expresie OR expresie										
			|	expresie_aritmetica											
			|	expresie_relationala									
			;												

expresie_aritmetica	:	expresie_aritmetica '+' expresie_aritmetica										
					|	expresie_aritmetica '-' expresie_aritmetica										
					|	expresie_aritmetica '*' expresie_aritmetica										
					|	expresie_aritmetica '/' expresie_aritmetica										
					|	expresie_aritmetica '%' expresie_aritmetica										
					|	STR											
					;

expresie_relationala	:	expresie_aritmetica GE expresie_aritmetica									
						|	expresie_aritmetica LE expresie_aritmetica																		
						|	expresie_aritmetica EQ expresie_aritmetica			
						|	expresie_aritmetica DIF expresie_aritmetica
						|	expresie_aritmetica '>' expresie_aritmetica										
						|	expresie_aritmetica '<' expresie_aritmetica					
						;

STR	:	CONST										
	| 	VAR											
	;

%%

yyerror(char *s)
{
  printf("%s\n", s);
}
extern FILE *yyin;

main(int argc, char **argv)
{
  if (argc > 1) 
    yyin = fopen(argv[1], "r");
  if ( (argc > 2) && ( !strcmp(argv[2], "-d") ) ) 
    yydebug = 1;
  if ( !yyparse() ) 
    fprintf(stderr,"\t Succes!\n");
}