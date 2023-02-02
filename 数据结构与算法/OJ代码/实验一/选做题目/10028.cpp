#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int cnt = 0;
typedef struct LNode
{
	int data;
	LNode* next;
}*linklist, LNode;
void TailInsert(linklist& l, int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		p->next = NULL;
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
}
void Count(linklist l,int mink,int maxk)
{
	linklist p = l->next;
	while (p)
	{
		if (p->data < mink || p->data > maxk)
			cnt++;
		p = p->next;
	}
}
void Go(linklist l, int mink, int maxk)
{
	linklist p = l->next;
	while (p)
	{
		if (p->data < mink || p->data > maxk)
		{
			cnt--;
			cout << p->data;
			if (cnt != 0)
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
	while (n)
	{
		linklist l;
		TailInsert(l,n);
		int mink, maxk;
		cin >> mink >> maxk;
		Count(l, mink, maxk);
		Go(l, mink, maxk);
		cnt = 0;
		cin >> n;
	}
	return 0;
}

