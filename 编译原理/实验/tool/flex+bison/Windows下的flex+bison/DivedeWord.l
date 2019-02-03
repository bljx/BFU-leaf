%option noyywrap
%{
#include<stdio.h>
int row = 1,col = 1;
%}
DIGIT[0-9]
ID[a-zA-Z][a-zA-Z0-9]*
%%
{DIGIT}+"."{DIGIT}*   {
		printf("2	%s\n",yytext);col = col + yyleng;
	}
{DIGIT}+   {
		printf("3	%s\n",yytext);col = col + yyleng;
	}

"/*"[^}\n]*"*/"  col = col + yyleng;

main        	printf("4      %s\n",yytext);col = col + yyleng;
return      	printf("5      %s\n",yytext);col = col + yyleng;
if          	printf("8      %s\n",yytext);col = col + yyleng;
else	    	printf("9      %s\n",yytext);col = col + yyleng;
then        	printf("10	%s\n",yytext);col = col + yyleng;	
for         	printf("11	%s\n",yytext);col = col + yyleng;
while       	printf("12	%s\n",yytext);col = col + yyleng;
do          	printf("13	%s\n",yytext);col = col + yyleng;
break       	printf("14	%s\n",yytext);col = col + yyleng;
continue    	printf("15	%s\n",yytext);col = col + yyleng;
switch      	printf("16	%s\n",yytext);col = col + yyleng;
case        	printf("17	%s\n",yytext);col = col + yyleng;
default     	printf("18	%s\n",yytext);col = col + yyleng;
int         	printf("19	%s\n",yytext);col = col + yyleng;
char        	printf("20	%s\n",yytext);col = col + yyleng;
float       	printf("21	%s\n",yytext);col = col + yyleng;
double      	printf("22	%s\n",yytext);col = col + yyleng;
void        	printf("23	%s\n",yytext);col = col + yyleng;
enum        	printf("24	%s\n",yytext);col = col + yyleng;
struct       	printf("25	%s\n",yytext);col = col + yyleng;
union       	printf("26	%s\n",yytext);col = col + yyleng;
long        	printf("27	%s\n",yytext);col = col + yyleng;
short       	printf("28	%s\n",yytext);col = col + yyleng;
signed      	printf("29	%s\n",yytext);col = col + yyleng;
unsigned    	printf("30	%s\n",yytext);col = col + yyleng;
static      	printf("31	%s\n",yytext);col = col + yyleng;
const       	printf("32	%s\n",yytext);col = col + yyleng;
typedef     	printf("33	%s\n",yytext);col = col + yyleng;
printf      	printf("68	%s\n",yytext);col = col + yyleng;
scanf       	printf("69	%s\n",yytext);col = col + yyleng;
include       	printf("70	%s\n",yytext);col = col + yyleng;
define       	printf("71	%s\n",yytext);col = col + yyleng;

"<"+{ID}+".h>"  printf("72	%s\n",yytext);col = col + yyleng;
["]+{ID}+".h"+["]  printf("73     %s\n",yytext);col = col + yyleng;
"/*"([^\*]|(\*)*[^\*/])*"*/"   col = col + yyleng; 

{ID}   		printf("1	%s\n",yytext);col = col + yyleng;

"%"    		printf("34	%s\n",yytext);col = col + yyleng;
"+"    		printf("35	%s\n",yytext);col = col + yyleng;
"-"    		printf("36	%s\n",yytext);col = col + yyleng;
"*"    		printf("37	%s\n",yytext);col = col + yyleng;
"/"    		printf("38	%s\n",yytext);col = col + yyleng;
"("    		printf("39	%s\n",yytext);col = col + yyleng;
")"    		printf("40	%s\n",yytext);col = col + yyleng;
"["    		printf("41	%s\n",yytext);col = col + yyleng;
"]"    		printf("42	%s\n",yytext);col = col + yyleng;
"{"    		printf("43	%s\n",yytext);col = col + yyleng;
"}"    		printf("44	%s\n",yytext);col = col + yyleng;
"->"   		printf("45	%s\n",yytext);col = col + yyleng;
"!"    		printf("46	%s\n",yytext);col = col + yyleng;
"++"   		printf("47	%s\n",yytext);col = col + yyleng;
"--"   		printf("48	%s\n",yytext);col = col + yyleng;
"<"    		printf("51  	%s\n",yytext);col = col + yyleng;
">"    		printf("52  	%s\n",yytext);col = col + yyleng;
"<<"   		printf("49  	%s\n",yytext);col = col + yyleng;
">>"   		printf("50  	%s\n",yytext);col = col + yyleng;
"<="   		printf("53  	%s\n",yytext);col = col + yyleng;
">="   		printf("54  	%s\n",yytext);col = col + yyleng;
"=="   		printf("55  	%s\n",yytext);col = col + yyleng;
"!="   		printf("56  	%s\n",yytext);col = col + yyleng;
"&&"   		printf("57  	%s\n",yytext);col = col + yyleng;
"||"   		printf("58  	%s\n",yytext);col = col + yyleng;
"^"    		printf("59  	%s\n",yytext);col = col + yyleng;
"="    		printf("60  	%s\n",yytext);col = col + yyleng;
"+="   		printf("61  	%s\n",yytext);col = col + yyleng;
"-="   		printf("62  	%s\n",yytext);col = col + yyleng;
"*="   		printf("63  	%s\n",yytext);col = col + yyleng;
"/="   		printf("64  	%s\n",yytext);col = col + yyleng;
"%="   		printf("65  	%s\n",yytext);col = col + yyleng;
","   		printf("66  	%s\n",yytext);col = col + yyleng;
";"   		printf("67  	%s\n",yytext);col = col + yyleng;
"#"       	printf("74  	%s\n",yytext);col = col + yyleng;
"**"       	printf("75  	%s\n",yytext);col = col + yyleng;
" "    		printf("76  	%s\n",yytext);col = col + yyleng;
"'"       	printf("77  	%s\n",yytext);col = col + yyleng;
\t		printf("78  	%s\n",yytext);col = col + yyleng;
\n		{
			row++;col = 0;
		}
.      		printf("不能识别字符：%s: row:%d,col:%d\n",yytext,row,col);
%%
main(void)
{
yylex();
}