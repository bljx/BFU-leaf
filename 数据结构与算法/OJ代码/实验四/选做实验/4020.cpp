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
	struct LNode* next;
}*linklist, LNode;
void Create(linklist& vl,int n)
{
	vl = new LNode[13];
	for (int i = 0; i < 13; i++)
	{
		vl[i].data = i;
		vl[i].next = NULL;
	}
	for (int i = 0; i <= n; i++)
	{
		int temp;
		cin >> temp;
		linklist p = &vl[temp%13], q = new LNode;
		while (p&&p->next)
			p = p->next;
		q->data = temp;
		q->next = NULL;
		p->next = q;
	}
}
void Show(linklist vl,int n)
{
	for (int i = 0; i < 13; i++)
	{
		linklist p = vl[i].next;
		cout << i;
		while (p)
		{
			cout << ' ';
			cout << p->data;
			p = p->next;
		}
		cout << endl;
	}
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		linklist vl;
		Create(vl, n);
		Show(vl, n);
	}
	return 0;
}

