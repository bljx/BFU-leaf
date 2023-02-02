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
}*linklist, LNode;
typedef struct
{
	linklist VList;
	int vexnum;
	int arcnum;
}ALGragh;
void Create(ALGragh& alg, int n, int m)
{
	alg.vexnum = n;
	alg.arcnum = m;
	alg.VList = new LNode[n+2];
	for (int i = 1; i <= n; i++)
	{
		alg.VList[i].vex = i;
		alg.VList[i].next = NULL;
	}
	int h, k;
	for (int i = 0; i < m; i++)
	{
		cin >> h >> k;
		linklist p=new LNode, q=new LNode;
		p->vex = h;
		p->next = alg.VList[k].next;
		q->vex = k;
		q->next = alg.VList[h].next;
		alg.VList[h].next = q;
		alg.VList[k].next = p;
	}
	int p;
	cin >> p;
	alg.VList[n + 1].vex = p;
	alg.VList[n + 1].next = NULL;
}
void Show(ALGragh alg,int n)
{
	for (int i = 1; i <= n + 1; i++)
	{
		linklist p = &alg.VList[i];
		while (p->next)
		{
			cout << p->vex;
			if (p->next)
				cout << ' ';
			p = p->next;
		}
		cout <<p->vex<< endl;
	}
}
int main()
{
	int m, n;
	while (cin >> n >> m && m != 0 && n != 0)
	{
		ALGragh a;
		Create(a, n, m);
		Show(a, n);
	}
	return 0;
}
