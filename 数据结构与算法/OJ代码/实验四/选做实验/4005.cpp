	#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
 
typedef struct LNode
{
	int vex;
	struct LNode* next;
}LNode, * linklist;
typedef struct
{
	linklist VList;
	int vexnum;
	int arcnum;
}ALGraph;
void Create(ALGraph& alg, int n, int m)
{
	alg.vexnum = n;
	alg.arcnum = m;
	alg.VList = new LNode[n + 1];
	for (int i = 1; i <= n; i++)
	{
		alg.VList[i].vex = i;
		alg.VList[i].next = NULL;
	}
	int h, k;
	for (int i = 0; i < m; i++)
	{
		cin >> h >> k;
		linklist p = new LNode, q = new LNode;
		p->vex = h;
		p->next = alg.VList[k].next;
		alg.VList[k].next = p;
		q->vex = k;
		q->next = alg.VList[h].next;
		alg.VList[h].next = q;
	}
}
void Show(ALGraph alg)
{
	int del;
	cin >> del;
	for (int i = 1; i <= alg.vexnum; i++)
	{
		if (i == del)
			continue;
		else
		{
			linklist p = &alg.VList[i];
			while (p->next)
			{
				if (p->vex == del)
					p = p->next;
				if (p)
				{
					cout << p->vex;
					if (p->next && p->next->vex != del)
						cout << ' ';
					p = p->next;
				}
			}
			if (p && p->vex != del)
				cout << p->vex << endl;
			else
				cout << endl;
		}
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
