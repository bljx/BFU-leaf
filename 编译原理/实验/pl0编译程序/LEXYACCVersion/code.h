/*  //////////////////////
// code.h
// 代码产生和控制相关
// 变量和操作
////////////////////// */

#include "table.h"
#define CXMAX 200
#define STACKSIZE 500


typedef enum fctType{/* 操作类型 */
	ini,
	lit,
	lod,
	sto,
	cal,
	jmp,
	jpc,
	opr
}fct;

typedef enum AppType{
	AP_ret=0,/* 函数返回操作 */
	AP_neg,/* 求反操作 */
	AP_add,/* 求和操作 */
	AP_sub,/* 求减操作 */
	AP_mul,/* 求乘操作 */
	AP_div,/* 求除操作 */
	AP_odd,/* 求奇操作 */
	AP_equ=8,/* 求是否相等操作 */
	AP_neq,/* 求是否不等操作 */
	AP_les,/* 求是否小于操作 */
	AP_gre,/* 求是否大于等于操作 */
	AP_grt,/* 求是否大于操作 */
	AP_lee,/* 求是否小于等于操作 */
	AP_wrt,/* 打印栈顶值操作 */
	AP_wtl,/* 打印换行操作 */
	AP_red/* 读取输入操作操作 */
}App;

typedef struct InstructionEnum{/* 指令结构定义 */
	fct f;
	int l;
	int a;
}Instruction;

static Instruction code[CXMAX];/* 指令数组 */
static int cx=-1;/* 当前产生指令的指针整数 */

int nextCode(){
	return cx+1;
}/* 获取下一条目标代码的位置 */

int getCodeApp(int index){/* 获取当前目标代码附加码的值 */
	return code[index].a;
}

void checkOverflow(){/* 检查代码是否溢出 */
	if(cx>=CXMAX)
		yyerror("too many codes.");
}

int gen(fct f,int l,App a){/* 生成一条目标代码 */
	cx++;
	checkOverflow();/* 检查代码是否溢出 */
	code[cx].f=f;
	code[cx].l=l;
	code[cx].a=a;
	return cx;
}

void backFill(int index){/* 回填指定目标代码附加码的值 */
	code[index].a=cx+1;
}

void listcode(FILE * file){/* 输出目标代码清单 */
	int i=0;
	for(;i<=cx;i++){
		fprintf(file,"%d.\t",i);
		switch(code[i].f){
			case ini:
				fprintf(file,"ini\t");
				break;
			case lit:
				fprintf(file,"lit\t");
				break;
			case lod:
				fprintf(file,"lod\t");
				break;
			case sto:
				fprintf(file,"sto\t");
				break;
			case cal:
				fprintf(file,"cal\t");
				break;
			case jmp:
				fprintf(file,"jmp\t");
				break;
			case jpc:
				fprintf(file,"jpc\t");
				break;
			case opr:
				fprintf(file,"opr\t");
				break;
		}
		fprintf(file,"%d\t%d\n",code[i].l,code[i].a);
	}
}

int base(int l,int beginIn,int stack[STACKSIZE]){/* 得到数据区基地址 */
	int returnInt=beginIn;
	while(l-->0)
		returnInt=stack[returnInt];
	return returnInt;
}

void interpret(FILE * file){/* 对目标代码进行解释执行 */
	int s[STACKSIZE]/* 运行指令的堆栈 */,tempInt;
	/* 执行指令需要的寄存器 */
	int p=0,t=-1,b=0;
	/* 目前执行的指令指针 */
	Instruction * i;
	/* 当前层的静态链和动态链 */
	int staticLink=0,dynamicLink=0;
	/* 堆栈的初始化 */
	s[0]=s[1]=s[2]=-1;
	do{
		i=code+p;
		switch(i->f){
			case ini:/* 开辟内存空间的操作 */
				t+=i->a;
				break;
			case lit:/* 把常量放到栈顶的操作 */
				s[++t]=i->a;
				break;
			case lod:/* 变量放到栈顶的操作 */
				/* 得到数据区基地址 */
				tempInt=base(i->l,b,s);
				s[++t]=s[tempInt+i->a];
				break;
			case sto:/* 存储栈顶数的操作 */
				/* 得到数据区基地址 */
				tempInt=base(i->l,b,s);
				s[tempInt+i->a]=s[t];
				t--;
				break;
			case cal:/* 函数调用的操作 */
				/* 得到数据区基地址 */
				tempInt=base(i->l,b,s);
				staticLink=s[t+1]=tempInt; 
				dynamicLink=s[t+2]=b;
				s[t+3]=p;
				p=i->a-1;
				b=t+1;
				break;
			case jmp:/* 无条件跳转的操作 */
				p=i->a-1;
				break;
			case jpc:/* 条件跳转的操作 */
				if(s[t]==0){
					p=i->a-1;	
				}
				t--;
				break;
			case opr:
				switch(i->a){
					case AP_ret:
						/* 函数返回的相关工作 */
						t=b-1;
						p=s[b+2];
						staticLink=s[b];
						dynamicLink=s[b+1];
						b=s[b];
						/* 当主函数结束后停止执行 */
						if(p==-1)
							return;
						if(dynamicLink==-1)
							return;
						break;
					case AP_neg:/* 求反操作 */
						s[t]=-s[t];
						break;
					case AP_add:/* 求和操作 */
						t--;
						s[t]+=s[t+1];
						break;
					case AP_sub:/* 求差操作 */
						t--;
						s[t]-=s[t+1];
						break;
					case AP_mul:/* 求积操作 */
						t--;
						s[t]*=s[t+1];
						break;
					case AP_div:/* 求商操作 */
						if(s[t]==0)
							error("Fatal Error: Divided By ZERO.\n");
						t--;
						s[t]/=s[t+1];
						break;
					case AP_odd:/* 求奇操作 */
						s[t]=(s[t]%2==0?0:1);
						break;
					case AP_equ:/* 求是否相同操作 */
						t--;
						s[t]=(s[t]==s[t+1]?1:0);
						break;
					case AP_neq:/* 求是否不同操作 */
						t--;
						s[t]=(s[t]!=s[t+1]?1:0);
						break;
					case AP_les:/* 求是否小于操作 */
						t--;
						s[t]=(s[t]<s[t+1]?1:0);
						break;
					case AP_gre:/* 求是否大于等于操作 */
						t--;
						s[t]=(s[t]>=s[t+1]?1:0);
						break;
					case AP_grt:/* 求是否大于操作 */
						t--;
						s[t]=(s[t]>s[t+1]?1:0);
						break;
					case AP_lee:/* 求小于等于操作 */
						t--;
						s[t]=(s[t]<=s[t+1]?1:0);
						break;
					case AP_wrt:/* 打印栈顶数操作 */
						if(file!=NULL)
							fprintf(file,"%d",s[t]);
						printf("%d",s[t]);
						break;
					case AP_wtl:/* 打印换行操作 */
						if(file!=NULL)
							fprintf(file,"\n");
						printf("\n");
						break;
					case AP_red:/* 读取输入至栈顶数操作 */
						if(file!=NULL)
							fprintf(file,"?");
						printf("?");
						scanf("%d",&s[++t]);
						if(file!=NULL)
							fprintf(file,"%d\n",s[t]);
						break;
					default:/* 未知操作报错 */
						error("Fatal Error: Unknown Operation.\n");
						break;
				}
				break;
			default:/* 未知操作报错 */
				error("Fatal Error: Unknown Operation.\n");
				break;
		}
		p++;
		if(t>=STACKSIZE)
				error("Fatal Error: Stack Overflow.\n");
	}while(1);
}