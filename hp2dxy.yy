%option noyywrap
%{

#include <math.h>

float xscale = 20;
float yscale = 20;

%}

%x PU
%x PD
%x SP


DIGIT	[0-9]
%%
<INITIAL>PU	{printf("M");BEGIN(PU);};
<INITIAL>PD	{printf("D");BEGIN(PU);};
<INITIAL>SP	{printf("J");BEGIN(SP);};
<INITIAL>IN;*	{printf("H\r");};
<PU,PD>{DIGIT}+	{
		printf("%d",(int)ceil(atoi(yytext)*1.0/xscale));
	}
<SP>{DIGIT}	{printf("%s",yytext);};
<PU,PD,SP>;	{printf("\r");BEGIN(INITIAL);};
;	printf("\r");
.	printf("%s",yytext);
%%
