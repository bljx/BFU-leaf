
/* //////////////////////
// pl0Lex.l
////////////////////// */  
%{	
	#include "stdio.h"
	#include "stdlib.h"
	#include "string.h"
	#include "pl0Yacc.h" 

	extern int errorLine;
%}


%%

[-+*/()]		{return yytext[0];}
[ \t]			{;}
"\n"			{errorLine++;}
"."				{return W_period;}
";"				{return W_semicolon;}
","				{return W_comma;}
"begin"			{return W_beginsym;}
"end"           		{return W_endsym;}
"var"           		{return W_varsym;}
"const"           	{return W_constsym;}
"procedure"       	{return W_procedure;}
":="              	{return W_becomes;}
"#"				{return W_neq;}
"="				{return W_eql;}
"<"				{return W_lss;}
">"				{return W_gtr;}
"<="			{return W_leq;}
">="			{return W_geq;}
"odd"			{return W_oddsym;}
"while"			{return W_whilesym;}
"do"			{return W_do;}
"if"				{return W_ifsym;}
"then"			{return W_thensym;}
"call"			{return W_callsym; }
"read"			{return W_readsym;}
"write"			{return W_writesym;}
[A-Za-z]([A-Za-z]|[0-9])*	{
				yylval.name=(char *)malloc(strlen(yytext)+1);
				strcpy(yylval.name,yytext);
				return W_ident;
}
[0-9]+			{
				yylval.value=atoi(yytext);
				return W_number;
}
.				{
				printf("Unknown word :\"%s\"\n",yytext);
}

%%


void redirectInput(FILE * input){/* 重定义输入流函数 */
	yyin=input;
}