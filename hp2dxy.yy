%option noyywrap
%{

#include <math.h>
#define EOLN	"\n"

float xscale = 20;
float yscale = 20;

%}

%x PU
%x PD
%x PA
%x SP
%s pen_up
%s pen_down


DIGIT	[0-9]
%%
<INITIAL>PU	{printf("M");BEGIN(PU);BEGIN(pen_up);};
<INITIAL>PD	{printf("D");BEGIN(PD);BEGIN(pen_down);};
<INITIAL>SP	{printf("J");BEGIN(SP);};
<INITIAL>IN;*	{printf("H"EOLN);};
<PU,PD,PA>{DIGIT}+	{
		printf("%d",(int)ceil(atoi(yytext)*1.0/xscale));
	}
<pen_up>PA		{printf(EOLN"M");BEGIN(PA);};
<pen_down>PA		{printf(EOLN"D");BEGIN(PA);};
<SP>{DIGIT}	{printf("%s",yytext);};
<PU,PD,SP,PA>;	{printf(EOLN);BEGIN(INITIAL);};
;	printf(EOLN);
.	printf("%s",yytext);
%%
