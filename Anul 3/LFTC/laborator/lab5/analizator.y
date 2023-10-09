%{
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1

%}

%error-verbose
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
%token EQUAL
%token CATTIMP
%token SFCATTIMP
%token EXECUTA

%%

S 	:	program											
	;

program	:	INT MAIN '(' ')' '{' lista_instr '}'					
		;
	
lista_instr	:	instr_decl lista_instr														
			|	instr_decl											
			;

instr_decl	:	instr											
			|	decl											
			;

instr	:	IF '(' expr ')' '{' lista_instr '}' ELSE '{' lista_instr '}'		
		|	IF '(' expr ')' '{' lista_instr '}'						
		|	FOR '(' instr_expr ';' instr_expr ';' instr_expr ')' '{' lista_instr '}'			
		|	CATTIMP '(' VAR ')' EXECUTA lista_instr SFCATTIMP
		|	CIN	VAR ';'									
		|	COUT X ';'									
		|	VAR '=' expr ';'							
		;
		
instr_expr	:	expr											
			|	CIN VAR											
			|	COUT X											
			| 	VAR '=' expr
			;

decl	:	INT VAR ';'									
		|	DOUBLE VAR ';'								
		;

expr	:	expr AND expr										
		|	expr OR expr										
		|	arithmetic_expr											
		|	relational_expr											
		;												

relational_expr	:	arithmetic_expr GE arithmetic_expr									
				|	arithmetic_expr LE arithmetic_expr									
				|	arithmetic_expr '>' arithmetic_expr										
				|	arithmetic_expr '<' arithmetic_expr										
				|	arithmetic_expr EQUAL arithmetic_expr									
				;
	
arithmetic_expr	:	arithmetic_expr '+' arithmetic_expr										
				|	arithmetic_expr '-' arithmetic_expr										
				|	arithmetic_expr '*' arithmetic_expr										
				|	arithmetic_expr '/' arithmetic_expr										
				|	arithmetic_expr '%' arithmetic_expr										
				|	X											
				;

X	:	CONST										
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
    fprintf(stderr,"\t U GOOOOOD !!!\n");
}
