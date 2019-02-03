%{
 /*识别Ｃ语言子集的词法分析程序*/
  #include "stdio.h"
%}
white          [\t\n\ ]
digit  [0-9]
letter          [A-Za-z]
id             ({letter}|[_])({letter}|{digit}|[_])*
%%
{white}+ ; 
int|char|while  	{Upper(yytext,yyleng); fprintf(yyout,"%s,KEY\n",yytext); }  
{id}         	{fprintf(yyout,"ID,%s\n",yytext); } 
/*=|{|}|(|)|;    	{fprintf(yyout,"%s,SYMBOL\n",yytext);}     */
"="|"{"|"}"|"("|")"|";"         {fprintf(yyout,"%s,SYMBOL\n",yytext);}
.          	{fprintf(yyout,"Unrecognized character: %s\n", yytext );}  
%%
  Upper(char *s,int l)
  {
     int i;
     for(i=0;i< l;i++)
       s[i]=toupper(s[i]);
  }
  main()  
  {   yyin = fopen("test.c", "r");
      yyout = fopen("result.txt", "w");
      if (yyin != NULL)   return yylex();
  }
