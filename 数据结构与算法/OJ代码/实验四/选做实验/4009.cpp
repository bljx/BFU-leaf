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
}*linklist, LNode;
typedef struct
{
	int vexnum;
	int arcnum;
	linklist VList;
}ALGraph;
void Create(ALGraph& alg, int n, int m)
{
	alg.arcnum = m;
	alg.vexnum = n;
	alg.VList = new LNode[n + 1];
	for (int i = 1; i <= n; i++)
	{
		alg.VList[i].data = i;
		alg.VList[i].next = NULL;
	}

	int h, k;
	for (int i = 0; i < m; i++)
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
		while (p->next)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << p->data << endl;
	}
}
void Delete(ALGraph& alg)//参数用引用说了多少遍了！！为什么记不住！！
{
	int h, k;
	cin >> h >> k;
	//还是先遍历删除再输出吧，好好做。。
	for (int i = 1; i <= alg.vexnum ; i++)
	{
		linklist p = &alg.VList[i];
		if (i == h)
		{
			if (p->next)
			{
				if (p->next->data == k)
					p->next = p->next->next;
			}
		}
		if (i == k)
		{
			if (p->next)
			{
				if (p->next->data == h)
					p->next = p->next->next;
			}
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
		Delete(a);
		Show(a);
	}
	return 0;
}

