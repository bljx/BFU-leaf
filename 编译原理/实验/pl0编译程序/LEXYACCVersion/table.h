/* //////////////////////
// table.h 
// 登记表相关变量和操作
////////////////////// */

#include "stdio.h"
#include "string.h"
#define LEVMAX 3
#define TXMAX 100
#define AL 10

typedef enum KindOfItemType{/* 变量类型 */
	CONSTANT,
	VARIABLE,
	PROCEDURE
}KindOfItem;

typedef struct ConstAppendixType{/* 常量附加结构定义 */
	int value;
}ConstAppendix;

typedef struct VarAppendixType{/* 变量附加结构定义 */
	int level;
	int address;
}VarAppendix;

typedef struct ProcAppendixType{/* 过程附加结构定义 */
	int level;
	int address;
}ProcAppendix;

typedef union AppendixInfoType{/* 附加联合,包含上述三个结构定义 */
	ConstAppendix constAppendix;
	VarAppendix varAppendix;
	ProcAppendix procAppendix;
}InfoAppendix;

typedef struct table1Type{/* 登记表的登记项目结构定义 */
	char nameOfItem[AL];
	KindOfItem kind;
	InfoAppendix append;
}table1;

static table1 table[TXMAX+1];/* 登记表的登记项目数组 */

static int levelIndexArray[LEVMAX];/* 已经编译到的各层所登记项个数的数组 */
static int levelRegisterArray[LEVMAX];/* 已经编译到的各层所需开辟空间大小的数组 */

static int currentLevelIndex/* 当前所在层登记项个数 */,currentLevelRegister;/* 当前所在层开辟空间大小 */
static int currentLevel=-1;/* 当前所在层 */

void startBlock(int alreadyExist){/* 开始编译一个新的Block的登记表的相应工作 */
	if(currentLevel==-1){
		currentLevelRegister=alreadyExist;
		currentLevelIndex=0;
		currentLevel++;
	}
	if(currentLevel==LEVMAX-1)
		yyerror("too many neasted block.\n");
	/* 相应的值更新 */
	levelIndexArray[currentLevel]=currentLevelIndex;
	levelRegisterArray[currentLevel]=currentLevelRegister;
	currentLevelRegister=alreadyExist;
	currentLevel++;
}

void endBlock(){/* 清除编译完成一个Block的变量 */
	currentLevel--;/* 层数减一 */
	/* 相应的值恢复 */
	currentLevelIndex=levelIndexArray[currentLevel];
	currentLevelRegister=levelRegisterArray[currentLevel];
}

int getLev(){/* 返回当前层 */
	return currentLevel;
}

int getLevVarNum(){/* 返回登记项寄存器 */
	return currentLevelRegister;
}

table1 getItem(int index){/* 返回登记项 */
	return table[index];
}

KindOfItem getKind(int index){/* 返回登记项的类型 */
	return table[index].kind;
}

void enterName(char *newName){/* 在符号表中登记一个新项的名称 */
	if (currentLevelIndex++<TXMAX){
		strcpy(table[currentLevelIndex].nameOfItem, newName);
	}else 
		yyerror("Too many items to register.\n");
}

int enterProc(char *newName)	{/* 在符号表中登记一个新的过程 */
	enterName(newName);/* 在符号表中登记一个新项的名称 */
	table[currentLevelIndex].kind=PROCEDURE;/* 登记过程类型 */
	table[currentLevelIndex].append.procAppendix.level=currentLevel;/* 登记过程的所在层 */
	/* 登记过程的入口地址为下一条目标代码的位置 */
	table[currentLevelIndex].append.procAppendix.address=nextCode();
	return currentLevelIndex;
}

int enterVar(char *newName)	{/* 在符号表中登记一个新的变量 */
	enterName(newName);/* 在符号表中登记一个新项的名称 */
	table[currentLevelIndex].kind=VARIABLE;/* 登记变量类型 */
	table[currentLevelIndex].append.varAppendix.level=currentLevel;/* 登记变量的所在层 */
	table[currentLevelIndex].append.varAppendix.address=currentLevelRegister++;/* 登记变量的地址 */
	return currentLevelIndex;
}

int enterConst(char *newName,int valueInput)	{/* 在符号表中登记一个新的常量 */
	enterName(newName);/* 在符号表中登记一个新项的名称 */
	table[currentLevelIndex].kind=CONSTANT;/* 登记常量类型 */
	table[currentLevelIndex].append.constAppendix.value=valueInput;/* 登记常量的值 */
	return currentLevelIndex;
}

int position(char *nameIn){/* 查找标识符在符号表中的位置 */
	int i;
	i=currentLevelIndex;
	strcpy(table[0].nameOfItem, nameIn);
	/* 寻找登记表中的定义项 */
	while(strcmp(nameIn,table[i].nameOfItem))
		i--;
	if(i!=0)
		return i;
	/* 如果没有找到则报错 */
	printf("Undefined ident : %s\n",nameIn);
	yyerror("");
	return 0;
}


