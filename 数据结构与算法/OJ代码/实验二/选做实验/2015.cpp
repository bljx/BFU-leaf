#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
typedef struct LSode
{
	char data;
	struct LSode* next;
}*LinkStack, Lsode;
void Init(LinkStack& ls)
{
	ls = NULL;
}
void Insert(LinkStack& ls, char c)
{
	LinkStack t = new LSode;
	t->data = c;
	t->next = ls;
	ls = t;
}
void PopNoPrint(LinkStack& ls)
{
	if (!ls) 
		exit(1);
	LinkStack t = ls;
	ls = ls->next;
	delete t;
}
void PopAndPrint(LinkStack& ls)
{
	if (!ls)  exit(1);
	LinkStack t = ls;
	ls = ls->next;
	if(t->data!='('&&t->data!=')')
		cout << t->data;
	delete t;
}
char GetTop(LinkStack ls)
{
	return ls->data;
}
char Compare(char a,char b)
{//a是栈里面的，b是新来的
	//>进栈，<不仅不进，a等等还要出栈
	if (b == '+' || b == '-')
	{
		if (a == '(')
			return '>';
		else return '<';
	}
	else if (b == '*' || b == '/')
	{
		if (a == '+' || a == '-'||a=='(')
			return '>';
		else return '<';
	}
}
void OutLoop(LinkStack& ls)
{
	if (ls != NULL)
	{
		while (ls->data != '(')
		{
			PopAndPrint(ls);
			if (ls == NULL) break;
		}
		if (ls != NULL)
			PopNoPrint(ls);//弹出'(',但是不打印
		else return;
	}
	else return;
}
void Ans(string s,LinkStack &l)
{
	for (int i = 0; i < s.length()-1; i++)
	{
		if (isdigit(s[i]))
			cout << s[i];
		else if (s[i] == '(')//不由分说地进栈
			Insert(l,s[i]);
		else if (s[i] == ')')//出栈吧！(此时）并未进栈
			OutLoop(l);
		else //既不是数字也不是左右括号
		{//只能是加减乘除之一了
			if (l == NULL)
				Insert(l, s[i]);
			else if (Compare(GetTop(l), s[i]) == '>')//进栈
				Insert(l, s[i]);
			else//一直出栈
			{
				OutLoop(l);
				Insert(l,s[i]);
			}
		}
	}
	OutLoop(l);
	cout << endl;
}
int main()
{
	string s;
	while (cin >> s && s != "=")
	{
		LinkStack l;
		Init(l);
		Ans(s,l);
	}
	return 0;
}

