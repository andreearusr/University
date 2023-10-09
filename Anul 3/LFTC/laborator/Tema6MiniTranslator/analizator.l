%{
#include <stdio.h>
#include <string.h>
#include "analizator.tab.h"
int lineNumber = 1;
%}

IDENTIFIER [a-zA-Z][a-zA-Z0-9]{0,7}
REAL_NUMBER   [+-]?(0|[1-9][0-9]*)
STRING 	   \".*\"			

%option noyywrap

%%
"int"                 { return INT; }
"main"                { return MAIN; }
"{"                   { return '{'; }
"}"                   { return '}'; }
"("                   { return '('; }
")"                   { return ')'; }
"+"                   { return '+'; }
"-"                   { return '-'; }
"*"                   { return '*'; }
"/"                   { return '/'; }
"="                   { return EQ; }
"cin >>"              { return IN; }
"cout <<"             { return OUT; } 
";"                   { return ';'; }
{IDENTIFIER}	{ strcpy(yylval.str, yytext); return ID; }
{REAL_NUMBER}	{ strcpy(yylval.str, yytext); return CONST; }
{STRING}		{ strcpy(yylval.str, yytext); return CONST; }
[\r\n]		 	{  lineNumber++;}
[ \t\n]+        { ; /* eat up whitespace */ }
.      		          { return(OTHER); }
