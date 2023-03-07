%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

COLOR_DIGIT	[0](\.[0-9]+)?|1(\.[0]+)?
COLOR_CHOICE	({COLOR_DIGIT}", "{COLOR_DIGIT}", "{COLOR_DIGIT})|blue|red|green
COLOR	"color "{COLOR_CHOICE}


DIGIT	[0-9]
FORWARD	"forward"|"fw"
BACKWARD	"backward"|"bw"
LEFT	"left"
RIGHT	"right"

%%

{COLOR}		{ printf("Color : %s\n",yytext); }	

{FORWARD}		{ return KW_FORWARD; }
 
{BACKWARD}		{ return KW_BACKWARD; }

{DIGIT}+		{ yylval.value = strtod(yytext, NULL); return VALUE; }

{LEFT}		{ return KW_LEFT; }

{RIGHT}		{ return KW_RIGHT; }

[\n\t ]*		/* whitespace */
.		{ fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
