%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(char *s);
extern FILE *yyin;
extern int lineNumber;

char DS[4096];
void addToDS(char *s);
char CS[4096];
void addToCS(char *s);

void writeToFile();
%}

%union{
	char str[250];
}

%token EQ
%token IN
%token OUT
%token OTHER
%token INT
%token MAIN
%token <str> ID
%token <str> CONST

%type <str> var
%type <str> const
%type <str> val
%type <str> expr

%%

program:  INT MAIN '(' ')' '{' decl instr '}' 
	   ;

decl: 
        | declaration ';' decl
		;

declaration: INT var
{
	char *tmp = (char*)malloc(sizeof(char)*250);
	sprintf(tmp, "%s dd 0\n", $2);
	addToDS(tmp);
	free(tmp);
}
		   ;

instr: 
		| instruction ';' instr
		;

instruction: assignment
		   | input
		   | output
		   ;

assignment: var EQ expr
{
	char *tmp = (char*)malloc(sizeof(char)*250);
	sprintf(tmp, "mov [%s], ebx\n", $1);
	addToCS(tmp);
	free(tmp);
}
		  ;

expr:   expr '+' val
{
	char *tmp = (char*)malloc(sizeof(char)*250);
	sprintf(tmp, "add ebx, %s\n", $3);
	addToCS(tmp);
	free(tmp);
}
        | expr '-' val
{
	char *tmp = (char*)malloc(sizeof(char)*250);
	sprintf(tmp, "sub ebx, %s\n", $3);
	addToCS(tmp);
	free(tmp);
}
		| expr '*' val
{
	char *tmp = (char*)malloc(sizeof(char)*250);
    strcpy(tmp, "mov eax, ebx\n");
    addToCS(tmp);
	sprintf(tmp, "mov ebx, %s\n", $3);
	addToCS(tmp);
	strcpy(tmp, "mul ebx\nmov ebx, eax\n");
	addToCS(tmp);
	free(tmp);
}
		| expr '/' val
{
	char *tmp = (char*)malloc(sizeof(char)*250);
    strcpy(tmp, "mov eax, ebx\n");
    addToCS(tmp);
	sprintf(tmp, "mov ebx, %s\n", $3);
	addToCS(tmp);
	strcpy(tmp, "mov edx, 0\ndiv ebx\nmov ebx, eax\n");
	addToCS(tmp);
	free(tmp);
}
        | val
{
	char *tmp = (char*)malloc(sizeof(char)*250);
	sprintf(tmp, "mov ebx, %s\n", $1);
	addToCS(tmp);
	free(tmp);
}
		;

val: var
{
	strcpy($$, "[");
	strcat($$, $1);
	strcat($$, "]");
}
	| const
{
	strcpy($$, $1);
}
	;

const:  CONST
{
	strcpy($$, $1);
}
        ;

input:  IN var
{
	char *tmp = (char*)malloc(sizeof(char)*250);
	sprintf(tmp, "push dword %s\npush dword in_format\ncall [scanf]\nadd esp, 4*2\n" ,$2);
	addToCS(tmp);
}
        ;

output: OUT var
{
	char *tmp = (char *)malloc(sizeof(char)*250);
	sprintf(tmp, "push dword [%s]\npush dword out_format\ncall [printf]\nadd esp, 4*2\n", $2);
	addToCS(tmp);
}
        ;

var: ID
{
	strcpy($$, $1);
}
    ;

%%

void addToDS(char *s){
    strcat(DS, s);
}

void addToCS(char *s){
    strcat(CS, s);
}

void yyerror(char *s)
{
	printf("%s la linia %d\n", s, lineNumber);
	exit(0);
}

int main(int argc, char** argv)
{
    memset(DS, 0, 4096);
    memset(CS, 0 ,4096);
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        yyparse();
		writeToFile();
    }
    return 0;
}

void writeToFile() {
	char *header = (char *) malloc(sizeof(char)*3000);
	char *dataSegment = (char *) malloc(sizeof(char)*3000);
	char *codeSegment = (char *) malloc(sizeof(char)*3000);
	char *footer = (char *) malloc(sizeof(char)*3000);
	
	strcpy(header, "bits 32\nglobal start\nextern exit, scanf, printf\nimport exit msvcrt.dll\nimport scanf msvcrt.dll\nimport printf msvcrt.dll\n");

	strcpy(dataSegment, "\nsegment data use32 class=data\nin_format db \"%d\", 0\nout_format db \"%d \", 0\n");
	strcat(dataSegment, DS);

	strcpy(codeSegment, "\nsegment code use32 class=code\nstart:\n");
	strcat(codeSegment ,CS);

	strcpy(footer, "\npush dword 0\ncall [exit]\n");

	FILE *f = fopen("code.asm", "w");
	if(f == NULL) {
		perror("Failed to write to file");
		exit(1);
	}

	fwrite(header, strlen(header), 1, f);
	fwrite(dataSegment, strlen(dataSegment), 1, f);
	fwrite(codeSegment, strlen(codeSegment), 1, f);
	fwrite(footer, strlen(header), 1, f);

	fclose(f);
	free(header);
	free(dataSegment);
	free(codeSegment);
	free(footer);
}