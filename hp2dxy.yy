%option noyywrap
%{

#include <math.h>

%}

float scale = 1;

DIGIT	[0-9]
%%
{DIGIT}+	{
		printf("Integer %s (%d)\n",yytext,atoi(yytext));
	}
.	printf("%s",yytext);
%%
