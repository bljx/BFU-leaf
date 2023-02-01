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
}*linklist, LNode;
void TailInsert(linklist& ji, linklist &ou,int n)
{
	ji = new LNode;
	ji->next = NULL;
	ou = new LNode;
	ou->next = NULL;
	linklist r1 = ji, r2 = ou;
	for (int i = 1; i <= n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		if (i % 2 != 0)// Ææ
		{
			r1->next = p;
			r1 = p;		
		}
		else
		{
			r2->next = p;
			r2 = p;
		}
	}
	r1->next = NULL;
	r2->next = NULL;
}
void Show(linklist ji,linklist ou)
{
	linklist p = ji->next;
	while (p)
	{
		cout << p->data;
		if (p->next)
			cout << " ";
		p = p->next;
	}
	p = ou->next;
	if (p)
		cout << " ";
	while (p)
	{
		cout << p->data;
		if (p->next)
			cout << " ";
		p = p->next;
	}
}
int main()
{
	int n;
	cin >> n;
	while (n)
	{
		linklist ji,ou;
		TailInsert(ji,ou,n);
		Show(ji,ou);
		cout << endl;
		cin >> n;
	}
	return 0;
}
