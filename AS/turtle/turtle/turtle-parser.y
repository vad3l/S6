%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
	double value;
	char *name;
	struct ast_node *node;
}

%token <value>		VALUE		"value"
%token <name>		 NAME		"name"
%token		KW_FORWARD		"forward"
%token		KW_BACKWARD		"backward"
%token		KW_LEFT		"DirectionLeft"
%token		KW_RIGHT		"DirectionRight"

/* TODO: add other tokens */

%type <node> unit cmds cmd expr

%%

unit:
		cmds		{ $$ = $1; ret->unit = $$; }
;

cmds:
		cmd cmds		{ $1->next = $2; $$ = $1; }
	| /* empty */		{ $$ = NULL; }
;

cmd:
		KW_FORWARD expr	 { 
			$$ = make_cmd_forward($2); 
		}
	|	KW_BACKWARD expr {
			$$ = make_cmd_backward($2)
		}


	|	KW_RIGHT {}
	|	KW_LEFT {}
;

expr:
		VALUE		{ $$ = make_expr_value($1); }
		/* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
	(void) ret;
	fprintf(stderr, "%s\n", msg);
}
