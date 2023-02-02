#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * linklist;
typedef struct
{
	int vexnum;
	int arcnum;
	linklist VList;
}ALGraph;
void Create(ALGraph& alg, int n, int m)
{
	alg.vexnum = n;
	alg.arcnum = m;
	alg.VList = new LNode[n + 1];
	for (int i = 1; i <= n; i++)
	{
		alg.VList[i].data = i;
		alg.VList[i].next = NULL;
	}
	int h, k;
	for (int i = 0; i <= m; i++)
	{
		cin >> h >> k;
		linklist p = new LNode, q = new LNode;
		p->data = h;
		p->next = alg.VList[k].next;
		alg.VList[k].next = p;

		q->data = k;
		q->next = alg.VList[h].next;
		alg.VList[h].next = q;
	}
}
void Show(ALGraph alg)
{
	for (int i = 1; i <= alg.vexnum; i++)
	{
		linklist p = &alg.VList[i];
		while (p)
		{
			cout << p->data;
			if (p->next)
				cout << ' ';
			p = p->next;
		}
		cout << endl;
	}
}
int main()
{
	int m, n;
	while (cin >> n >> m && m != 0 && n != 0)
	{
		ALGraph a;
		Create(a, n, m);
		Show(a);
	}
	return 0;
}

