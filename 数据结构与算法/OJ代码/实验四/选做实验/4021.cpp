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
void Create(linklist& vl, int n)
{
	vl = new LNode[13];
	for (int i = 0; i < 13; i++)
	{
		vl[i].data = i;
		vl[i].next = NULL;
	}
	//β�巨
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		linklist p = new LNode, r = &vl[temp % 13];
		while (r->next)
			r = r->next;
		p->data = temp;
		p->next = NULL;
		r->next = p;
	}
}
void Show(linklist vl)
{
	int x;
	cin >> x;
	for (int i = 0; i < 13; i++)
	{
		cout << i;
		linklist p = vl[i].next;
		while (p)
		{
			if (p->data == x)
				cout << "";
			else
				cout <<' '<< p->data;
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
		Show(vl);
	}
	return 0;
}
