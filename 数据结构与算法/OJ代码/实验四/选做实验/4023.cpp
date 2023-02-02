#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

typedef struct LNode
{
	int data;
	struct LNode* prior, * next;
}*linklist, LNode;
void Init(linklist &l)
{
	l = new LNode;
	l->next = NULL;
	l->prior = NULL;
}
void Insert(linklist& l,int n)
{
	int x;
	linklist p=l;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		linklist temp = new LNode;
		temp->data = x;
		temp->next = l->next;
		l->next = temp;
		temp->prior = l;
		l = temp;
	}
	l = p;
}
void Sort(linklist &l)
{
	linklist p=l->next,f;
	while (p->next)
		p = p->next;
	linklist r = p;
	f = l->next;
	while (1)
	{
		if (f != r)
		{
			for (p = f; p != r; p = p->next)
			{
				if (p->data > p->next->data)
				{
					int t = p->data;
					p->data = p->next->data;
					p->next->data = t;
				}
			}
			r = r->prior;
		}
		else break;
		if (f != r)
		{
			for (p = r; p != f; p = p->prior)
			{
				if (p->data < p->prior->data)
				{
					int t = p->data;
					p->data = p->prior->data;
					p->prior->data = t;
				}
			}
			f = f->next;
		}
		else break;
	}
}
void Print(linklist l)
{
	linklist p = l->next;
	while (p->next)
	{
		cout << p->data << ' ';
 		p = p->next;
	}
	cout << p->data << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		linklist l;
		Init(l);
		Insert(l, n);
		Sort(l);
		Print(l);
	}
	return 0;
}

