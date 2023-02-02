#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int b = 0, c = 0;
typedef struct LNode
{
	int data;
	struct LNode* next;
}*linklist, LNode;
void Init(linklist &l)
{
	l = new LNode;
	l->next = NULL;
}
void TailInsert(linklist& l, int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		if (p->data < 0)
			b++;
		else
			c++;
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
}
void B(linklist l)
{
	linklist p = l->next;
	while(p)
	{
		if (p->data < 0)
		{
			b--;
			cout << p->data;
			if (b != 0)
				cout << " ";
		}
		p = p->next;
	}
	cout << endl;
}
void C(linklist l)
{
	linklist p = l->next;
	while (p)
	{
		if (p->data > 0)
		{
			c--;
			cout << p->data;
			if (c != 0)
				cout << " ";
		}
		p = p->next;
	}
	cout << endl;
}
int main()
{
	int n;
	cin >> n;
	while (n != 0)
	{
		linklist l;
		Init(l);
		TailInsert(l, n);
		B(l);
		C(l);
		b = 0;
		c = 0;
		cin >> n;
	}
	return 0;
}

