
/* //////////////////////
// pl0Yacc.y
////////////////////// */
%{
	#include "stdio.h" 
	#include "extra.h"
	#include "code.h"
	
	
	#define FILENAME_LENGTH 30
    
	int errorLine=1;
    	int noError=1;
%}

%union{
	char *name;
	int value;
}

%token W_period W_semicolon W_comma W_beginsym W_endsym
%token W_varsym W_constsym W_procedure W_becomes
%token W_oddsym W_neq W_eql W_lss W_gtr W_leq W_geq
%token W_whilesym W_do W_ifsym W_thensym W_callsym W_readsym W_writesym  
%token W_ident W_number

%token <name> W_ident
%token <value> W_number

%%

program	: /* 开始新的过程并保存当前过程的数据 */					
		{startBlock(3);}
	block W_period
	;

block	:/* 开始新的过程之前的跳转代码，跳转位置在后面回填 */
		{$<value>$=gen(jmp,0,0);/* 生成一条目标代码 */}
	declareList	
		{backFill($<value>1);/* 回填指定目标代码附加码的值 */
		/* 为新的过程产生开辟内存空间生成一条目标代码 */
		gen(ini,0,getLevVarNum()/* 获取当前层变量的数目 */);}
	statement	
		{gen(opr,0,AP_ret);/* 为新的过程之后返回生成一条目标代码 */
		endBlock();/* 结束、跳出目前的过程并更新过程有关的数据 */}
	;
declareList	: /* null */
		|declareList declare
		;
declare	:constDeclare
	|varDeclare
	|procedureDeclare
	; 
constDeclare: W_constsym constList W_semicolon
	;
constList	: W_ident W_eql W_number	
			{enterConst($1,$3);	}/* 在符号表中登记一个新的常量 */
		| constList W_comma W_ident W_eql W_number
			{enterConst($3,$5);	}/* 在符号表中登记一个新的常量 */
		;
varDeclare	: W_varsym varList W_semicolon
		;
varList		: W_ident
			{enterVar($1);}/* 在符号表中登记一个新的变量 */
		| varList W_comma W_ident
			{enterVar($3);}/* 在符号表中登记一个新的变量 */
		;
procedureDeclare: W_procedure W_ident W_semicolon
			{enterProc($2);	/* 在符号表中登记一个新的过程 */
			/* 开始新的过程并保存当前过程的数据 */
			startBlock(3); }
		block W_semicolon
		;
statement	: /* null */
		| W_ident W_becomes expression
			{/* 产生赋值表达式对应的目标代码 */
			int l,a;
			table1 tempR;
			/* 通过查找标识符在符号表中的位置来获取符号表中的一项 */
			tempR= getItem(position($<name>1));
			/* 获取当前所在的层和变量所在层的层差 */
			l=getLev()-tempR.append.varAppendix.level;
			a= tempR.append.varAppendix.address;
			gen(sto,l,a);/* 生成一条目标代码 */}
		| W_beginsym statement statementList W_endsym
		| W_ifsym condition W_thensym	
			{$<value>$=gen(jpc,0,0);/* 生成一条条件跳转目标代码 */}
		statement
			{backFill($<value>4);}/* 回填指定目标代码附加码的值 */
		| W_whilesym
			{$<value>$=nextCode();}/* 获取下一条目标代码的位置 */
		condition W_do
			{$<value>$=gen(jpc,0,0);/* 生成一条条件跳转目标代码 */}
		statement
			{gen(jmp,0,$<value>2);/* 生成一条无条件跳转目标代码 */
			backFill($<value>5);/* 回填指定目标代码附加码的值 */}
		| W_readsym '(' identList ')'            				
		| W_writesym '(' expressionList ')'	            		
			{gen(opr,0,AP_wtl);}/* 生成一条打印目标代码 */
		| W_callsym W_ident	
			{	/* 产生函数调用代码 */
			int l,a;
			table1 tempR;
			/* 通过查找标识符在符号表中的位置来获取符号表中的一项 */
			tempR= getItem(position($<name>2));
			/* 获取当前所在的层和过程所在层的层差 */
			l=getLev()-tempR.append.procAppendix.level;
			/* 获取当前目标代码附加码的值 */
			a=getCodeApp(tempR.append.procAppendix.address);
			/* 生成一条函数调用目标代码 */
			gen(cal,l,a);}
			;
statementList: /* null */
		| statementList W_semicolon statement
		;
condition	: W_oddsym expression 
			{gen(opr,0,AP_odd);/* 生成一条目标代码 */}
		| expression W_eql expression             		
			{gen(opr,0,AP_equ);/* 生成一条目标代码 */}
		| expression W_neq expression        	
			{gen(opr,0,AP_neq);/* 生成一条目标代码 */}
		| expression W_lss expression              		
			{gen(opr,0,AP_les);/* 生成一条目标代码 */}
		| expression W_gtr expression            	
			{gen(opr,0,AP_grt);/* 生成一条目标代码 */}
		| expression W_leq expression         	
			{gen(opr,0,AP_lee);/* 生成一条目标代码 */}
		| expression W_geq expression     	
			{gen(opr,0,AP_gre);/* 生成一条目标代码 */}
		;
identList	: W_ident                                   				
			{	/* 产生读命令对应的代码 */
			int l,a;
			table1 tempR;
			/* 通过查找标识符在符号表中的位置来获取符号表中的一项 */
			tempR= getItem(position($<name>1));
			/* 获取当前所在的层和变量所在层的层差 */
			l=getLev()-tempR.append.varAppendix.level;
			a=tempR.append.varAppendix.address;
			gen(opr,0,AP_red);/* 生成一条目标代码 */
			/* 生成一条储存栈顶数至变量的目标代码 */
			gen(sto,l,a);}
		| identList W_comma W_ident  				
			{	/* 产生读命令对应的代码 */
			int l,a;
			table1 tempR;
			/* 通过查找标识符在符号表中的位置来获取符号表中的一项 */
			tempR= getItem(position($<name>3));
			/* 获取当前所在的层和变量所在层的层差 */
			l=getLev()-tempR.append.varAppendix.level;
			a=tempR.append.varAppendix.address;
			gen(opr,0,AP_red);/* 生成一条目标代码 */
			/* 生成一条储存栈顶数至变量的目标代码 */
			gen(sto,l,a);}
			;
expressionList: expression 
			{gen(opr,0,AP_wrt);/* 生成一条目标代码 */}
		| expressionList W_comma expression		
			{gen(opr,0,AP_wrt);/* 生成一条目标代码 */}
			;
expression	: term
		| '+' term
		| '-' term 									
			{gen(opr,0,AP_neg);/* 生成一条目标代码 */}
		| expression '+' term                            			
			{gen(opr,0,AP_add);/* 生成一条目标代码 */}
		| expression '-' term							
			{gen(opr,0,AP_sub);/* 生成一条目标代码 */}
		;
term		: factor
		| term '*' factor								
			{gen(opr,0,AP_mul);/* 生成一条目标代码 */}
		| term '/' factor                      					
			{gen(opr,0,AP_div);/* 生成一条目标代码 */}
		;
factor	: W_ident									
		{/* 对于用户定义标识符的操作（变量和常量）和产生相应代码 */
		int index, kind,l,a,tempInt;
		table1 tempR;
		/* 查找标识符在符号表中的位置 */
		index=position($<name>1); 
		/* 获取符号表中登记项的数据类型 */
		kind=getKind(index);
		switch(kind){
		     	case VARIABLE:
				/* 获取符号表中的一项 */
				tempR= getItem(index);
				tempInt= tempR.append.varAppendix.level;
				/* 获取当前所在的层和变量所在层的层差 */
				l=getLev()-tempInt;
				a=tempR.append.varAppendix.address;
				gen(lod,l,a);/* 生成一条变量放到栈顶目标代码 */
				break;
		     	case CONSTANT:
				/* 通过查找标识符在符号表中的位置来获取符号表中的一项 */
				tempR=getItem(position($<name>1));
				a=tempR.append.constAppendix.value;
				gen(lit,0,a);/* 生成一条常量放到栈顶的目标代码 */
				break; 
}}
	| W_number     								
		{gen(lit,0,$<value>1);/* 生成一条目标代码 */}
	| '(' expression ')'
	;

%%

void yyerror(char* s) {
  fprintf(stderr, s);
  fprintf(stderr,"\tOn Line %d\n",errorLine);
  noError = 0;
}
                
void main(int argc,char ** argv){
	FILE * fileIn=NULL,* fileOut=NULL;/* 定义文件输入输出流 */
	char fileName[FILENAME_LENGTH];
	int haveOutFile=0; 
	if(argc>1){
		fileIn=fopen(argv[1],"r");
		if(fileIn==NULL)
			error("Error in reading file.");		 
		if(argc==3){
			fileOut=fopen(argv[2],"w");
			if(fileOut==NULL)
				error("Error in opening file.");
			haveOutFile=1;
		}
	}
	else{
		printf("Input file:");
		gets(fileName,FILENAME_LENGTH);
		fileIn=fopen(fileName,"r");
		if(fileIn==NULL)
			error("Error in reading file.");
		/* 询问是否输出编译结果至文件 */
		if(yesOrNoQuestion("Write compiled codes to file")){
			printf("Output to compileRes.txt\n");
			fileOut=fopen("compileRes.txt","w");
			if(fileOut==NULL)
				error("Error in opening [compileRes.txt] file.");
			haveOutFile=1;
		}
	}
	redirectInput(fileIn);/* 重定义输入流 */
	yyparse();/* 编译的过程 */
	if(noError){/* 编译没有错误时执行 */
		if(yesOrNoQuestion("List the compiled codes on screen"))
			listcode(stdout);/* 输出目标代码清单至屏幕 */
		if(haveOutFile)
			listcode(fileOut);/* 输出目标代码清单至文件 */
		if(yesOrNoQuestion("Execute the program")){	
			haveOutFile=0;
			/* 询问是否输出运行结果至文件 */
			if(yesOrNoQuestion("Output the execute result to file")){
				printf("Output to executeRes.txt\n");
				fileOut=fopen("executeRes.txt","w");
				if(fileOut==NULL)
					error("Error in opening [executeRes.txt] file.");
				haveOutFile=1;
			}   
			printf("\tStarting the program\n");
			if(haveOutFile)
				interpret(fileOut);/* 对目标代码进行解释执行并把结果存至文件 */
			else
				interpret(NULL);/* 对目标代码进行解释执行并输出至屏幕 */
			printf("\tProgram terminated\n");
		}
	}
	if(fileIn!=NULL)
		fclose(fileIn);
	if(fileOut!=NULL)
		fclose(fileOut);
}
