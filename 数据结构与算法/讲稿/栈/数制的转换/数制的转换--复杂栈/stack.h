 /* stack.h 栈的顺序存储表示 */
 
 #define OK 1
 #define ERROR 0
 typedef int Status; 
 #define  SIZE 50 /* 存储空间初始分配量 */
 typedef struct SqStack
 {
   SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
   SElemType *top; /* 栈顶指针 */
   int stacksize;
 }SqStack; /* 顺序栈 */

 Status InitStack(SqStack &S)
 { /* 构造一个空栈S */
   S.base=new SElemType[SIZE];
   if(!S.base)
     exit(OVERFLOW); /* 存储分配失败 */
   S.top=S.base;
   S.stacksize=SIZE;
   return OK;
 }


 bool StackEmpty(SqStack S)
 { /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
   if(S.top==S.base)
     return true;
   else
     return false;
 }

void Push(SqStack &S,SElemType e)
 { /* 插入元素e为新的栈顶元素 */
   if(S.top-S.base==S.stacksize) /* 栈满 */
	   cout<<"栈满，无法压栈!"<<endl;
   *S.top++=e;
 }
int Pop(SqStack &S,int &e)
 { /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
   if(S.top==S.base)
     return ERROR;
   e=*--S.top;
   return e;
 }

