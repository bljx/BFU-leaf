                         /*PL/0 编译系统C版本头文件 pl0.h*/

# define norw 13                 /*关键字个数*/
# define txmax 100               /*名字表容量*/
# define nmax  14                /*number的最大位数*/
# define al 10                   /*符号的最大长度*/
# define amax 2047               /*地址上界*/
# define levmax 3                /*最大允许过程嵌套声明层数[0，lexmax]*/
# define cxmax 200               /*最多的虚拟机代码数*/
/*符号*/
enum symbol{
	 nul,    ident,     number,     plus,     minus,
	 times,   slash,   oddsym,   eql,     neq,
lss,     leq,      gtr,     geq,     lparen,
rparen,  comma,   semicolon,period,  becomes,
beginsym, endsym, ifsym,    thensym,  whilesym,
writesym, readsym,  dosym,  callsym,  constsym,
varsym,  procsym,
};
#define symnum 32
/*-------------*/
enum object{
   constant,
   variable,
   procedur,
};
/*--------------*/
enum fct{
lit, opr,  lod,  sto,  cal,  inte,  jmp,  jpc,
};
#define fctnum 8
/*--------------*/
struct instruction
{
  enum fct f;
  int l;
  int a;
};

FILE * fas;
FILE * fa;
FILE * fa1;
FILE * fa2;

bool tableswitch;
bool listswitch;
char ch;
enum symbol sym;
char id[al+1];
int  num;
int cc,ll;
int cx;
char line[81];
char a[al+1];
struct instruction code[cxmax];
char word[norw][al];
enum symbol wsym[norw];
enum symbol ssym[256];
char mnemonic[fctnum][5];
bool declbegsys[symnum];
bool statbegsys[symnum];
bool facbegsys[symnum];
/*------------------------------*/




struct tablestruct
{
   char name[al];                            /*名字*/
   enum object kind;                         /*类型：const，var，array or procedure*/
   int val;                                  /*数值，仅const使用*/
   int level;                                /*所处层，仅const不使用*/
   int adr;                                  /*地址，仅const不使用*/
   int size;                                 /*需要分配的数据区空间，仅procedure使用*/
};
struct tablestruct table[txmax];             /*名字表*/
FILE * fin;
FILE* fout;
char fname[al];
int err;                                       /*错误计数器*/
/*当函数中会发生fatal error时，返回－1告知调用它的函数，最终退出程序*/
#define getsymdo                              if(-1==getsym())return -1
#define getchdo                               if(-1==getch())return -1
#define testdo(a,b,c)                         if(-1==test(a,b,c))return -1
#define gendo(a,b,c)                          if(-1==gen(a,b,c))return -1
#define expressiondo(a,b,c)                   if(-1==expression(a,b,c))return -1
#define factordo(a,b,c)                       if(-1==factor(a,b,c))return -1
#define termdo(a,b,c)                         if(-1==term(a,b,c))return -1
#define conditiondo(a,b,c)                    if(-1==condition(a,b,c))return -1
#define statementdo(a,b,c)                    if(-1==statement(a,b,c))return -1
#define constdeclarationdo(a,b,c)             if(-1==constdeclaration(a,b,c))return -1
#define vardeclarationdo(a,b,c)               if(-1==vardeclaration(a,b,c))return -1
void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x,int y,int z);
int test(bool*s1,bool*s2,int n);
int inset(int e,bool*s);
int addset(bool*sr,bool*s1,bool*s2,int n);
int subset(bool*sr,bool*s1,bool*s2,int n);
int mulset(bool*sr,bool*s1,bool*s2,int n);
int block(int lev,int tx,bool* fsys);
void interpret();
int factor(bool* fsys,int* ptx,int lev);
int term(bool*fsys,int*ptx,int lev);
int condition(bool*fsys,int*ptx,int lev);
int expression(bool*fsys,int*ptx,int lev);
int statement(bool*fsys,int*ptx,int lev);
void listcode(int cx0);
int vardeclaration(int* ptx,int lev, int* pdx);
int constdeclaration(int* ptx,int lev, int* pdx);
int position(char* idt,int tx);
void enter(enum object k,int* ptx,int lev,int* pdx);
int base(int l,int* s,int b);

        








