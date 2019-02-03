%{
typedef char* string;
#define YYSTYPE string
%}
%token NAME EQ PRICE
%%
file : record file
     | record        
     ; 
record : NAME EQ PRICE { printf("%s is %s yuan!\n", $1, $3); }
       ;       
%%
int main() 
{      
  yyparse(); 
  return 0;    
}        
void yyerror(char *msg)
{ 
  printf("Error encountered: %s \n", msg);
}
