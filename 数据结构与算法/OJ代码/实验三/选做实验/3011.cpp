#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
/*3011
   《我爱祖国的蓝天》
   《歌唱祖国》
*/
typedef struct BNode
{
	int num;
	char op;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
typedef struct TreeNode
{
	BTree data;
	struct TreeNode* next;
}*Tstack, TNode;
typedef struct OptrNode
{
	char optr;
	struct OptrNode* next;
}*Ostack, ONode;
char PopNoPrint(Ostack& os)
{
	if (os)
	{
		char temp = os->optr;
		Ostack t = os;
		os = os->next;
		delete t;
		//不打印，返回值
		return temp;
	}
}
char TOP(Ostack os)
{
	if (os)	return os->optr;
}
BTree PopNoPrint(Tstack& ts)//把返回值改成了BTree
{
	if (ts)
	{
		BTree temp = ts->data;
		Tstack t = ts;
		ts = ts->next;
		delete t;
		//不打印，返回值
		return temp;
	}
}
void InitStack(Ostack& os,Tstack& ts)
{
	os = NULL;
	ts = NULL;
}
BTree CreateTree(char c, BTree& l, BTree& r)
{
	//改了，不是bt = new BNode;
	BTree temp = new BNode;
	temp->op = c;
	temp->lchild = l;
	temp->rchild = r;
	return temp;
}
BTree CreateTree(int a, BTree& l, BTree& r)
{
	//改了，不是bt = new BNode;
	BTree temp = new BNode;
	temp->num = a;
	temp->lchild = l;
	temp->rchild = r;
	return temp;
}
void InStack(Ostack& os,char c)//运算符入栈
{
	Ostack temp = new ONode;
	temp->optr = c;
	temp->next = NULL;
	temp->next = os;
	os = temp;
}
void InStack(Tstack& ts, BTree bt)//树入栈
{
	Tstack temp = new TNode;
	temp->data = bt;
	temp->next = ts;
	ts = temp;
}
int RUOptr(char ch)	//判断读入的字符ch是否为运算符
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '=')
		return true;
	else return false;
}
int cmp(char a,char b)//比较运算符优先级
{
	if (a == '*' || a == '/')
	{
		if (b == '(')
			return -1;
		else
			return 1;
	}
	if (a == '+' || a == '-')
	{
		if (b == '*' || b == '/' || b == '(')
			return -1;
		else
			return 1;
	}
	if (a == '(')
		if (b == ')')
			return 0;
		else return -1;

	if (a == '=')
		if (b == '=')
			return 0;
		else
			return -1;
	else return 1;
}
int Operate(int a, char theta, int b)
{
	switch (theta)
	{
	case '+':return a + b; break;
	case '-':return a - b; break;
	case '*':return a * b; break;
	case '/':return a / b; break;
	default:break;
	}
}
int Calculate(BTree bt)
{
	if (!bt)
		return 0;
	if (!bt->lchild && !bt->rchild)
	{    //左右子树都为空，说明该节点是个符号，需要运算
		return bt->num;
	}
	else
	{
		int lvalue=0, rvalue=0;
		lvalue = Calculate(bt->lchild);
		rvalue = Calculate(bt->rchild);
		return Operate(lvalue, bt->op, rvalue);
	}
}
void Build(BTree& bt)
{
	Tstack t;
	Ostack o;
	InitStack(o, t);
	InStack(o, '=');
	char c;
	cin >> c;
	if (c == '=')
		exit(0);
	while (TOP(o) != '='||c!='=')
	{
		if (!RUOptr(c))//不是运算符
		{
			BTree temp = NULL;//这句!
			InStack(t, CreateTree(c-'0', temp, temp));
			cin >> c;
		}
		else//是运算符
		{
			if (cmp(TOP(o), c)==-1)//优先级高于当前字符
			{
				InStack(o, c);//入栈
				cin >> c;
			}
			else if(cmp(TOP(o),c)==1)//弹符弹数做运算后入栈
			{	//这里若能加以改进……
				BTree x = new BNode, y = new BNode;
				x = PopNoPrint(t), y = PopNoPrint(t);
				BTree root = CreateTree(PopNoPrint(o), x, y);
				InStack(t, root);
				bt = root;////////////////////////////////
			}
			else//是'='，说明一个是'（'一个是'）'
			{
				PopNoPrint(o);//'('出栈
				cin >> c;
			}
		}
	}
}

int main()
{
	while (1)
	{
		BTree b;
		Build(b);
		cout << Calculate(b) << endl;
	}
	return 0;
}
