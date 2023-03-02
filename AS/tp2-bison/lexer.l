%{
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
ID    [A-Z][A-Z0-9]*
COMMSINGLE \/\/.*\n
COMMULTI  \/\*(.|\n)*\*\/
%%

"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }
"("	      { return '('; }
")"	      { return ')'; }
"\n"          { return '\n'; }
"QUIT"	      { exit(0); }

{DIGIT}+      { yylval.value = strtod(yytext, NULL); return VALUE; }
{ID}          { yylval.name = strdup(yytext); return NAME; }
{COMMULTI}    /* nothing */
{COMMSINGLE}  /* nothing */
[\t ]*        /* nothing */
.             { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
