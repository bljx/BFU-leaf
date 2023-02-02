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
	int p;
	cin >> p;
	cout << p << ' ';
	int i = 0;
	linklist q = &alg.VList[p];
	stack<int> s;
	while (q->next)
	{
		s.push(q->next->data);
		q = q->next;
		i++;
	}
	while (!s.empty())
	{
		cout << s.top();
		if (i != 1)
			cout << ' ';
		s.pop();
		i--;
	}
	cout << endl;
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
