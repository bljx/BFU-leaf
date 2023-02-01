#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;
map<char, int> mp;
typedef struct LNode
{
	char data;
	struct LNode* next;
}*linklist, LNode;
typedef struct
{
	int arcnum;
	int vexnum;
	linklist VList;
}ALGraph;
void Create(ALGraph& alg, int n, int m)
{
	alg.arcnum = m;
	alg.vexnum = n;
	alg.VList = new LNode[n + 1];
	string ves;
	cin >> ves;

	for (int i = 0; i < ves.length(); i++)
		mp[ves[i]] = i + 1;
	int j = 0;
	for (int i = 1; i <= n; i++)
	{
		alg.VList[i].data = ves[j++];
		alg.VList[i].next = NULL;
	}
	map<char, int>::iterator it = mp.begin();
	for (int i = 0; i < m; i++)
	{
		string t;
		cin >> t;
		linklist p = new LNode;
		p->data = t[1];
		while (it != mp.end())
		{
			if (it->first == t[0])
			{
				p->next = alg.VList[it->second].next;
				alg.VList[it->second].next = p;
				break;
			}
			it++;
		}
	}
}
int GetPos(char c)
{
	map<char, int>::iterator it = mp.begin();
	int pos = 0;
	while (it != mp.end())
	{
		if (it->first == c)
		{
			pos = it->second;
			break;
		}
		it++;
	}
	return pos;
}
void Find(ALGraph alg,int k)
{
	string t;
	cin >> t;
	int pos = GetPos(t[0]);
	linklist p = &alg.VList[pos];
	int len = 0;
	while (p)
	{
		len++;
		p = p->next;
		if (p->data == t[1])
			break;
		else
		{
			pos = GetPos(p->data);
			p = &alg.VList[pos];
		}
	}
	if (len != k)
		cout << "NO" << endl;
	else
		cout << "YES" << endl;
}
int main()
{
	int m, n, k;
	while (cin >> n >> m >>k&& m != 0 && n != 0&&k!=0)
	{
		ALGraph a;
		Create(a, n, m);
		Find(a, k);
	}
	return 0;
}

