%option noyywrap
%{

#include <math.h>
#include "y.tab.h"

#define EOLN	"\n"

extern int yylval;

//Resolution in mm
#define	MDG116_RES	(0.1)
#define HPGL_RES	(0.025)

float xscale = 4;
float yscale = 4;

%}

%x PU
%x PD
%x PA
%x SP


DIGIT	[0-9]
NUMBER	{DIGIT}+
COORDINATE	{NUMBER},{NUMBER}
COORDINATES	{COORDINATE}
WHITESPACE	[ \r\n\t]*
%%
{WHITESPACE}	{ };
{NUMBER}	{ yylval= atoi(yytext); return NUMBER; };
IN	{ return INITIAL; }
PU	{ return PEN_UP; }
PD	{ return PEN_DOWN;}
SP	{ return SELECT_PEN;}
.	{ yyerror("token not recognized"); }
%%
