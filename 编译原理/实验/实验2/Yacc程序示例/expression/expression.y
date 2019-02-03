%{
#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double 	/*定义语义栈为double类型*/
%}
%token NUMBER	/*文法开始符定义省略*/
%left '+', '-'	/*优先级最低*/
%left '*', '/'
%right UMINUS	/*虚拟运算符，它和一元减有相同的优先级*/
%%
lines	: lines expr '\n'	{ printf("%g\n", $2); }
 	| lines '\n'
 	| /*空串 */
	| error '\n'	{ yyerror("reenter last line:"); yyerrok(); }
	;
expr	: expr '+' expr	{ $$ = $1 + $3; }
	| expr '-' expr	{ $$ = $1 - $3; }
	| expr '*' expr	{ $$ = $1 * $3; }
	| expr '/' expr	{ $$ = $1 / $3; }
	| '(' expr ')'	{ $$ = $2; }
	| '(' expr error	{ $$ = $2; yyerror("missing ')'"); yyerrok(); }
	| '-' expr %prec UMINUS	{ $$ = -$2; }
	| NUMBER
	;
  %%
  int yylex(void)
  {
  int c;
   while ((c = getchar()) == ' ');
  if (c == '.' || isdigit(c)) {
	ungetc(c, stdin);
	scanf("%lf", &yylval);
	return NUMBER;
  }
  return c;
 }    
