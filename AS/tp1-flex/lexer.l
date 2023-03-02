%{
#include <stdio.h>
#include <stdlib.h>
%}

%option warn 8bit nodefault noyywrap

BOOL	"true"|"false"
INT	(0|[1-9])[0-9]*
HEX	[a-fA-F0-9]+
IDC	[a-zA-Z_][A-Za-z_0-9]*

%%

{INT}+	{
		printf("Integer: %i (%s)\n", atoi(yytext), yytext);
	}
{BOOL}+ {
		printf("Boolean: %s\n", yytext);
	}
0x{HEX}	{
		printf("Hexadecimal: %x (%s)\n", atoi(yytext), yytext);
	}
{INT}+"."{INT}* {
		printf("Flottant: %f\n", atof(yytext));
	}
{INT}*"."{INT}+ {
		printf("Flottant: %f\n", atof(yytext));
	}
{INT}*"."{INT}+[eE][+-]{0,1}{INT}* {
		printf("Flottant: %f\n", atof(yytext));
	}
{INT}+[eE][+-]{0,1}{INT}* {
		printf("Flottant: %f (%s)\n", atof(yytext), yytext);
	}
I|PI|CIRCLE|POLY5 {
		printf("Symbol: %s\n", yytext);
	}
{IDC}+ {
		printf("Identifiant: %s\n", yytext);
	}
[\n\t ]*  /* nothing */
.         { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
