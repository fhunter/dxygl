%option noyywrap
%{

#include <math.h>

%}

%x PU
%x PD
%x SP

float scale = 1;

DIGIT	[0-9]
%%
<INITIAL>PU	{printf("Pen UP");BEGIN(PU);};
<INITIAL>PD	{printf("Pen DOWN");BEGIN(PU);};
<INITIAL>IN;*	{printf("H\n");};
<PU,PD>{DIGIT}+	{
		printf("Integer %s (%d)\n",yytext,atoi(yytext));
	}
<PU,PD>;	BEGIN(INITIAL);
.	printf("%s",yytext);
%%
