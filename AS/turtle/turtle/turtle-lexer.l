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


DIGIT	-?[0-9]
FORWARD	"forward"|"fw"
BACKWARD	"backward"|"bw"
LEFT	"left"
RIGHT	"right"
UP	"up"|"Up"
DOWN  "down"|"Down"
REPEAT	"repeat"
POSITION	"position" 

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

"random"	{ return KW_RANDOM; }
","		{ return ','; }
{COLOR}		{ return KW_COLOR; }
<<<<<<< HEAD

{POSITION}		{ return KW_POSITION; }

=======
>>>>>>> f655407ab06cf0af87ebf8a64178dc43098c54da
{REPEAT}		{ return KW_REPEAT; }
{FORWARD}		{ return KW_FORWARD; }
{BACKWARD}		{ return KW_BACKWARD; }
{UP}		{ return KW_UP; }
{DOWN}		{ return KW_DOWN; }
{DIGIT}+		{ yylval.value = strtod(yytext, NULL); return VALUE; }
<<<<<<< HEAD

{COLOR_DIGIT}+		{ yylval.value = strtod(yytext, NULL); return VALUE; }

=======
{COLOR_DIGIT}+		{ yylval.value = strtod(yytext, NULL); return VALUE; }
>>>>>>> f655407ab06cf0af87ebf8a64178dc43098c54da
{LEFT}		{ return KW_LEFT; }
{RIGHT}		{ return KW_RIGHT; }

[\n\t ]*		/* whitespace */
.		{ fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
