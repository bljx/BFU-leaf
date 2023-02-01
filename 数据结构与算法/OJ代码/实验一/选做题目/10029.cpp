#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>
using namespace std;
typedef struct LNode
{
	int data;
	LNode* next;
	LNode* prior;
}*linklist, LNode;
void TInsert(linklist& l, int n)
{
	l = new LNode;
	cin >> l->data;
	l->next = NULL;
	linklist r = l;
	for (int i = 1; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		r->next = p;
		p->prior = r;
		r = p;
	}
	r->next = l;
	l->prior = r;
}
void Change(linklist& l, int n)
{
	linklist p = l;
	int i = 1;
	while (p && i < n-1 )
	{
		p = p->next;
		i++;
	}
	int temp = p->data;
	p->data = p->next->data;
	p->next->data = temp;
}
void Show(linklist l)
{
	linklist p = l;
	cout << p->data << " ";
	p = l->next;
	while (p != l)
	{
		cout << p->data;
		if (p->next != l)
			cout << " ";
		p = p->next;
	}
	cout << endl;
}
int main()
{
	int n;
	cin >> n;
	while (n)
	{
		linklist l;
		TInsert(l,n);
		cin >> n;
		Change(l, n);
		Show(l);
		cin >> n;
	}
	return 0;
}

