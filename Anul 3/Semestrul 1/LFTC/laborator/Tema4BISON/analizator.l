%{
#include <stdio.h>
#include <stdlib.h>
#include "analizator.tab.h" // generated via bison -d
int lineNumber = 1;
%}

%option noyywrap


IDENTIFIER [a-zA-Z][a-zA-Z0-9]{0,7}
REAL_NUMBER   [+-]?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][+-][0-9]*)?
STRING 	   \".*\"			
OCTAL 0[0-7]*  				
HEXAZECIMAL 0(x|X)[0-9A-Ea-e]+([eE][+-][0-9])?		
BINAR (0b|0B)(0|1)+			

/*** Rule Section ***/
%%
"#include"   	{ return INCLUDE; }
"<iostream>" 	{ return IOSTREAM; }
"using"      	{ return USING; }
"namespace"  	{ return NAMESPACE; }
"std"        	{ return STD; }
"int"        	{ return INT; }
"main"     		{ return MAIN; }
"const"     	{ return CONST; }
"double"     	{ return DOUBLE; }
"cin"       	{ return CIN; }
"cout"      	{ return COUT; }
"if"         	{ return IF; }
"else"       	{ return ELSE; }
"for"      		{ return FOR; }
"while"      	{ return WHILE; }
"endl"     		{ return ENDL; }

">>"			{ return IN; }
"<<" 			{ return OUT; }

"+"          	{ return '+'; }
"-"          	{ return '-'; }
"*"          	{ return '*'; }
"/"          	{ return '/'; }
"%"          	{ return '%'; }

"="          	{ return '='; }
"&&"			{return AND;}
"||"			{ return OR;}
"=="         	{ return EQ; }
">="         	{ return GE; }
"<="         	{ return LE; }
"!="         	{ return DIF; }
">"          	{ return '>'; }
"<"        	 	{ return '<'; }


"("          	{ return '('; }
")"          	{ return ')'; }
"{"          	{ return '{'; }
"}"          	{ return '}'; }
";"          	{ return ';'; }
","          	{ return ','; }


{IDENTIFIER}	{ return VAR; }
{REAL_NUMBER}	{ return CONST; }
{OCTAL}			{ return CONST; }
{HEXAZECIMAL}	{ return CONST; }
{BINAR}			{ return CONST; }
{STRING}		{ return CONST; }
[\r\n]		 	{  lineNumber++;}
[ \t\n]+        { ; /* eat up whitespace */ }
. 			 	{ printf("Illegal token %s at line %d", yytext, lineNumber); printf("\n"); exit(0); }
%%