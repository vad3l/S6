%{
#include <stdio.h>
#include "main.h"

int yylex();
void yyerror(const char *);

%}

%debug
%defines

%define parse.error verbose

%union {
  double value;
  const char *name;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%left '+' '-'
%left '*' '/'
%left '(' ')'

%type <value> expr

%%

input:
    /* empty */
  | input line
;

line:
    '\n'
  | expr '\n'         { printf("> %.10g\n", $1); }
;

expr:
    VALUE             { $$ = $1; }
  | NAME              { $$ = constant($1); }
  | expr '+' expr     { $$ = $1 + $3; printf("addition\n"); }
  | '-' expr	      { $$ = -$2; }
  | expr '-' expr     { $$ = $1 - $3; }
  | expr '*' expr     { $$ = $1 * $3; printf("multiplication\n"); }
  | expr '/' expr     { $$ = $1 / $3; }
  | '(' expr ')'      { $$ = $2; }
;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "%s\n", msg);
}
