/* 中缀符号计算器 */

%{
        #define YYSTYPE double          /*定义语义值的C数据类型*/
        #include <math.h>
        #include <stdio.h>
        #include <ctype.h>
        int yylex (void);
        void yyerror (char const *);
%}

%token NUM      /*记号类型,仅有NUM一种*/
%left '-' '+'   /*定义+,-运算为左结合*/

/* 所谓左结合是指1+2+3这个表达式
   是这样计算的: (1+2)+3
   而最明显的右结合x=y=z则这么算:x=(y=z)
 */
%left '*' '/'   /*越靠后优先级越高*/
%left NEG       /*由于负号与减号相同,这里用另一个符号注明,后面有说明*/
%right '^'      /*幂运算为右结合*/

%%
input:          /*输入可以是空串,这使当程序一开始就接收到EOF不致于发生错误*/
        | input line    /*也可以是一行*/
;

line:     '\n'  /*一行可以简单的一个回车,这时忽略处理*/
        | exp '\n'  { printf ("\t%.10g\n", $1); }
                /*如果是表达式,则打印exp的语义值,而本句的语义值将被废弃*/
;

exp:      NUM                { $$ = $1;         }
                /*表达式可以仅为一个数字,这时赋值本句的语义值为此数字*/
        | exp '+' exp        { $$ = $1 + $3;    }
                /*表达式可以为一个表达式加上另一个,相应的语义值也相加,下同*/
        | exp '-' exp        { $$ = $1 - $3;    }
        | exp '*' exp        { $$ = $1 * $3;    }
        | exp '/' exp        { $$ = $1 / $3;    }
        | '-' exp  %prec NEG { $$ = -$2;        }
                /*出现这种语法结构则它的优先级与NEG相同*/
        | exp '^' exp        { $$ = pow ($1, $3); }
        | '(' exp ')'        { $$ = $2;         }
;
%%

/*主函数直接调用yyparse进行分析*/
int main (void)
{
        return yyparse ();
}

/*词法分析函数
  这本来是lex该做的东西,这里换手写了
  这个函数简单地把流中的数字挑出来,其它的以字符形式返回
  返回小于或等于0则yyparse会认为输入结束
 */
int yylex (void)
{
        int c;

        while ((c = getchar ()) == ' ' || c == '\t');

        if (c == '.' || isdigit (c)) {
                ungetc (c, stdin);
                scanf ("%lf", &yylval);
                return NUM;
        }

        if (c == EOF) return 0;
        return c;
}

/*错误处理,简单地打印出来*/
void yyerror (char const *s)
{
        fprintf (stderr, "%s\n", s);
}
