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
%token		KW_REPEAT		"repeat"
%token		KW_COLOR		"color"
%token		KW_FORWARD		"forward"
%token		KW_BACKWARD		"backward"
%token		KW_LEFT		"DirectionLeft"
%token		KW_RIGHT		"DirectionRight"
%token		KW_UP		"up"
%token		KW_DOWN		"down"
%token		KW_RANDOM	"random"
%token		KW_POSITION	"position"
%token		KW_HOME		"home"
%token		KW_HEADING	"heading"
%token		KW_COS		"cos"
%token		KW_SIN		"sin"
%token		KW_TAN		"tan"
%token		KW_SQRT		"sqrt"

%token		KW_COLOR_BLUE	"blue"
%token		KW_COLOR_RED	"red"
%token		KW_COLOR_GREEN	"green"
%token		KW_COLOR_CYAN	"cyan"
%token		KW_COLOR_MAGENTA	"magenta"
%token		KW_COLOR_YELLOW	"yellow"
%token		KW_COLOR_BLACK	"black"
%token		KW_COLOR_GRAY	"gray"
%token		KW_COLOR_WHITE	"white"

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
		KW_RANDOM '('expr ',' expr ')' { $$ = make_cmd_random($3, $5); }
	|	KW_COLOR_BLUE	{ $$ = make_cmd_color(0.0 ,0.0 ,1.0); }
	|	KW_COLOR_RED	{ $$ = make_cmd_color(1.0 ,0.0 ,0.0); }
	|	KW_COLOR_GREEN	{ $$ = make_cmd_color(0.0 ,1.0 ,0.0); }
	|	KW_COLOR_CYAN	{ $$ = make_cmd_color(0.0 ,1.0 ,1.0); }
	|	KW_COLOR_MAGENTA	{ $$ = make_cmd_color(1.0 ,0.0 ,1.0); }
	|	KW_COLOR_YELLOW	{ $$ = make_cmd_color(1.0 ,1.0 ,0.0); }
	|	KW_COLOR_BLACK	{ $$ = make_cmd_color(0.0 ,0.0 ,0.0); }
	|	KW_COLOR_GRAY	{ $$ = make_cmd_color(0.5 ,0.5 ,0.5); }
	|	KW_COLOR_WHITE	{ $$ = make_cmd_color(1.0 ,1.0 ,1.0); }
	|	KW_COLOR	expr ',' expr ',' expr	{ $$ = make_cmd_color_rgb($2,$4,$6); }
	|	KW_FORWARD expr	{ $$ = make_cmd_forbackward(true,$2); }
	|	KW_BACKWARD expr	{$$ = make_cmd_forbackward(false,$2); }
	|	KW_RIGHT expr	{$$ = make_cmd_rotate(false,$2); }
	|	KW_LEFT	expr	{$$ = make_cmd_rotate(true,$2); }
	|	KW_UP	{ $$ = make_cmd_pencilLead(true); }
	|	KW_DOWN	{ $$ = make_cmd_pencilLead(false); }
	|	KW_POSITION	expr ',' expr { $$ = make_cmd_position($2,$4); }
	|	KW_REPEAT	{}
	|	KW_HOME	{ $$ = make_cmd_home(); }
	|	KW_HEADING expr	{ $$ = make_cmd_heading($2); }
	|	KW_COS	'(' expr ')'	{}
	|	KW_SIN	'(' expr ')'	{}
	|	KW_TAN	'(' expr ')'	{}
	|	KW_SQRT	'(' expr ')'	{}
;

expr:
		VALUE		{ $$ = make_expr_value($1); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
	(void) ret;
	fprintf(stderr, "%s\n", msg);
}
