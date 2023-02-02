#include<iostream>
using namespace std;
#define OK 1
#define ERROR -1

//链栈的存储结构
typedef struct StackNode
{
	char data;
	struct StackNode* next;
}StackNode, * LinkStack;

//链栈的初始化
int InitStack(LinkStack& S)
{//构造一个空栈，栈顶指针置空
	S = NULL;
	return OK;
}

int Push(LinkStack& S, char e)
{//在栈顶插入元素
	LinkStack p = new StackNode;//生成新结点
	p->data = e;//将新节点的 数据域置为e
	p->next = S;//将新结点插入栈顶
	S = p;//修改栈顶指针为p
	return OK;
}

char Pop(LinkStack& S, char& e)
{
	if (S == NULL)
		return ERROR;//栈空
	e = S->data;//将栈顶元素赋给e
	LinkStack p = S;//用p临时保存栈顶元素空间，以备释放
	S = S->next;//修改栈顶指针
	delete p;//释放原栈顶元素的空间
	return e;
}

//取栈顶元素
char GetTop(LinkStack S)
{//当栈顶非空时，此操作返回当前栈顶元素的值，栈顶指针S保持不变
	if (S != NULL)
		return S->data;
	else
		return '?';
}


//链栈的存储结构
typedef struct StackNoded
{
	double data;
	struct StackNoded* next;
}StackNoded, * LinkStackd;

//链栈的初始化
int InitStackd(LinkStackd& S)
{//构造一个空栈，栈顶指针置空
	S = NULL;
	return OK;
}

//链栈的入栈
int Pushd(LinkStackd& S, double e)
{//在栈顶插入元素
	LinkStackd p = new StackNoded;//生成新结点
	p->data = e;//将新节点的 数据域置为e
	p->next = S;//将新结点插入栈顶
	S = p;//修改栈顶指针为p
	return OK;
}

//链栈的出栈
double Popd(LinkStackd& S, double& e)
{
	if (S == NULL)
		return -1;//栈空
	e = S->data;//将栈顶元素赋给e
	LinkStackd p = S;//用p临时保存栈顶元素空间，以备释放
	S = S->next;//修改栈顶指针
	delete p;//释放原栈顶元素的空间
	return e;
}

//取栈顶元素
double GetTopd(LinkStackd S)
{//当栈顶非空时，此操作返回当前栈顶元素的值，栈顶指针S保持不变
	if (S != NULL)  return S->data;
	else return ERROR;
}
//判断读入的字符ch是否为运算符
int In(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*'|| ch == '/' || ch == '(' || ch == ')' || ch == '=')
		return true;
	else return false;
}

//比优先级
char Precede(char ch1, char ch2)
{
	switch (ch1)
	{
	case '?':
		return '<';
	case '+':
		if (ch2 == '+' || ch2 == '-' || ch2 == ')' || ch2 == '=')
			return '>';
		else
			return '<';
	case '-':
		if (ch2 == '+' || ch2 == '-' || ch2 == ')' || ch2 == '=')
			return '>';
		else
			return '<';
	case '*':
		if (ch2 == '+' || ch2 == '-' || ch2 == '*' || ch2 == '/' || ch2 == ')' || ch2 == '=')
			return '>';
		else
			return '<';
	case '/':
		if (ch2 == '+' || ch2 == '-' || ch2 == '*' || ch2 == '/' || ch2 == ')' || ch2 == '=')
			return '>';
		else
			return '<';
	case '(':
		if (ch2 == '+' || ch2 == '-' || ch2 == '*' || ch2 == '/' || ch2 == '(')
			return '<';
		else if (ch2 == '=')
			return '>';
		else
			return '=';
	case ')':
		if (ch2 == '+' || ch2 == '-' || ch2 == '*' || ch2 == '/' || ch2 == ')' || ch2 == '=')
			return '<';
		else  return ' ';
	}
}

double Operate(double a, char theta, double b)
{
	switch (theta)
	{
		case '+':return a + b;break;
		case '-':return a - b;break;
		case '*':return a * b;break;
		case '/':return a / b;break;
		default:break;
	}
}

double EvaluateExpression(char* str)
{//算术表达式求值的算符优先法，设OPND和OPTR分别为操作数栈和运算符栈
	char ch;//当前字符
	LinkStack OPTR;
	LinkStackd OPND;
	InitStackd(OPND);//初始化OPND栈
	InitStack(OPTR);//初始化OPTR栈
	ch = str[0];
	int i = 0;//扫描字符串的下标
	//运算符 运算数a 运算数b
	char theta, x;
	double a,b;
	int i1 = 0;//数字和小数点构成的字符串下标
	char z[10] = {};//存放数字的字符串
	while (true)
	{
		ch = str[i];//第i个字符
		if (ch == '\0')
			break;
		if (In(ch))//是运算符
		{
			ch = str[i];
			switch (Precede(GetTop(OPTR), ch))
			{//比较OPTR的栈顶元素和ch的优先级
			case '<':
				Push(OPTR, ch);
				i++;
				ch = str[i];
				break;
			case '>':
				Pop(OPTR, theta);//弹出栈顶的运算符
				Popd(OPND, b); 
				Popd(OPND, a);//弹出栈顶的两个运算数
				Pushd(OPND, Operate(a, theta, b));//将运算结果压入OPND栈
				break;
			case '='://OPTR的栈顶元素是"("且ch")"
				Pop(OPTR, x);
				i++;
				ch = str[i];
				break;
			default:break;
			}
		}
		else if (ch >= '0' && ch <= '9')//数字
		{
			i1 = 0;
			do
			{
				z[i1++] = ch;
				i++;
				ch = str[i];
			} while ((ch >= '0' && ch <= '9') || ch == '.');
			z[i1] = 0;
			Pushd(OPND, atof(z));
		}
		else break;
	}
	return GetTopd(OPND);
}

int main()
{
	char str[50] = {};//输入的字符串算术表达式
	char ch;
	double output;
	while (1)
	{
		cin >> str;
		ch = str[0];
		if (ch == '=')  break;

		else  printf("%.2f\n", EvaluateExpression(str));
	}
}
