%{
#include "p2.h"  
#include <stdio.h>
#include <string.h>
extern char* yylval; 
%}
char [A-Za-z]
num [0-9]
eq [=]
name {char}+ 
price {num}+
%%
{name} { yylval = strdup(yytext);   return NAME; }   
{eq} { return EQ; }
{price} { yylval = strdup(yytext);  return PRICE; }
%%   
int yywrap()
 { return 1;}
