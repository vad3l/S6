%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT   [0-9]
FORWARD "forward"|"fw"
LEFT    "left"
RIGHT   "right"

%%

{FORWARD} { return KW_FORWARD;}
 
{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }

{LEFT}{0,1} { return KW_LEFT; }

{RIGHT}{0,1} { return KW_RIGHT; }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%