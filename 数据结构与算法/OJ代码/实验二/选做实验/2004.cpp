#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
typedef struct Stack
{
	struct Stack* next;
	int data;
}stk,*linkstack;
void Init(linkstack& s)
{s = NULL;}
void Push(linkstack& s,int x)
{
	linkstack t = new stk;
	t->data = x;
	t->next = s;
	s = t;
}
void Pop(linkstack& s)
{
	cout << s->data << endl;
	linkstack t = s;
	s=t->next;
	delete t;
}
bool Empty(linkstack s)
{return s == NULL;}
int main()
{
	int n;
	cin >> n;
	while (n != 0)
	{
		linkstack s;
		Init(s);
		int a[100];
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for(int i=0;i<n;i++)
		{
			if (a[i] == -1&&!Empty(s))
				Pop(s);
			else if (a[i] == -1 && Empty(s))
			{
				cout << "POP ERROR" << endl;
				break;
			}
			else
				Push(s,a[i]);
		}
		cin >> n;
	}
	return 0;
}
