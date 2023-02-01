#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
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
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
}
void Find(linklist l, int n,int pos)
{
	linklist p = l->next;
	for (int i = 1; i <= n; i++)
	{
		if (i == n-pos+1)
		{
			cout << p->data << endl;
			break;
		}
		p = p->next;
	}
}
int main()
{
	int n;
	cin >> n;
	while (n)
	{
		linklist l;
		TailInsert(l,n);
		int pos;
		cin >> pos;
		Find(l, n, pos);
		cin >> n;
	}
	return 0;
}
