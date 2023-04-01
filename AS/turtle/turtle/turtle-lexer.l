%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

COLOR_BLUE	"color blue"
COLOR_RED	"color red"
COLOR_GREEN	"color green"
COLOR_CYAN	"color cyan"
COLOR_MAGENTA	"color magenta"
COLOR_YELLOW	"color yellow"
COLOR_BLACK	"color bkack"
COLOR_GRAY	"color gray"
COLOR_WHITE	"color white"

COLOR_DIGIT	[0](\.[0-9]+)?|1(\.[0]+)?
COLOR	"color"

IDC	[A-Z_][A-Z_0-9]*
DIGIT	[0-9]+(.[0-9]+)?
FORWARD	"forward"|"fw"
BACKWARD	"backward"|"bw"
LEFT	"left"|"lt"
RIGHT	"right"|"rt"
HEADING	"heading"|"hd"
UP	"up"|"Up"
DOWN  "down"|"Down"
REPEAT	"repeat"
POSITION	"position" 
RANDOM		"random"
HOME		"home"
COS		"cos"
SIN		"sin"
TAN		"tan"
SQRT	"sqrt"
PROC	"proc"
SET		"set"

%%

{COLOR_BLUE}	{ return KW_COLOR_BLUE; }
{COLOR_RED}	{ return KW_COLOR_RED; }
{COLOR_GREEN}	{ return KW_COLOR_GREEN; }
{COLOR_CYAN}	{ return KW_COLOR_CYAN; }
{COLOR_MAGENTA}	{ return KW_COLOR_MAGENTA; }
{COLOR_YELLOW}	{ return KW_COLOR_YELLOW; }
{COLOR_BLACK}	{ return KW_COLOR_BLACK; }
{COLOR_GRAY}	{ return KW_COLOR_GRAY; }
{COLOR_WHITE}	{ return KW_COLOR_WHITE; }
{COLOR}		{ return KW_COLOR; }

","		{ return ','; }
"("		{ return '('; }
")"		{ return ')'; }

"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
"%"		{ return '%'; }
"^"		{ return '^'; }

"{"		{ return '{'; }
"}"		{ return '}'; }

{IDC}		{ yylval.name = yytext; printf("yytext = %s\n", yytext); return NAME; }
{POSITION}		{ return KW_POSITION; }
{RANDOM}	{ return KW_RANDOM; }
{REPEAT}		{ return KW_REPEAT; }
{FORWARD}		{ return KW_FORWARD; }
{BACKWARD}		{ return KW_BACKWARD; }
{UP}		{ return KW_UP; }
{DOWN}		{ return KW_DOWN; }
{LEFT}		{ return KW_LEFT; }
{RIGHT}		{ return KW_RIGHT; }
{HOME}		{ return KW_HOME; }
{HEADING}	{ return KW_HEADING; }
{COS}		{ return KW_COS; }
{SIN}		{ return KW_SIN; }
{TAN}		{ return KW_TAN; }
{SQRT}		{ return KW_SQRT; }		
{PROC}		{ return KW_PROC; }
{SET}		{ return KW_SET; }

{DIGIT}+		{ yylval.value = strtod(yytext, NULL); return VALUE; }
{COLOR_DIGIT}+		{ yylval.value = strtod(yytext, NULL); return VALUE; }

[\n\t ]*		/* whitespace */
.		{ fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
