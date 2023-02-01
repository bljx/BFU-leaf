#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<unordered_map>
using namespace std;

typedef struct LNode
{
	char data;
	struct LNode* next;
}*linklist, LNode;
typedef struct
{
	linklist VList;
	int vnum;
	int anum;
}ALGraph;
unordered_map<char, int> mp;
int visit[30];
int GetPos(char c,unordered_map<char,int>mp)
{
	unordered_map<char, int>::iterator it = mp.begin();
	while (it != mp.end())
	{
		if (it->first == c)
			return it->second;
		it++;
	}
	return 0;
}
void Create(ALGraph& alg, int n, int m)
{
	alg.anum = m;
	alg.vnum = n;
	alg.VList = new LNode[alg.vnum + 1];
	string s;
	cin >> s;
	for (int i = 1; i <= n; i++)
	{
		alg.VList[i].data = s[i];
		alg.VList[i].next = NULL;
		mp.insert(make_pair(s[i-1], i));
	}
	for (int i = 0; i < m; i++)
	{
		cin >> s;
		int pos = GetPos(s[0],mp);
		linklist p = &alg.VList[pos], q = new LNode;
		q->data = s[1];
		q->next = p->next;
		p->next = q;
	}
}
void DFS(ALGraph alg,char from,char to)
{
	if (from == to)
	{
		cout << "YES" << endl;
		return;
	}
	int pos = GetPos(from, mp);
	linklist p = &alg.VList[pos];
	visit[pos] = 1;
	if (p->next)
	{
		DFS(alg, p->next->data, to);
		visit[pos] = 0;
	}
	else
	{
		cout << "NO" << endl;
		return;
	}
}
int main()
{
	int n, m;
	while (cin >> n >> m && n != 0 && m != 0)
	{
		ALGraph a;
		Create(a, n, m);
		string s;
		cin >> s;
		char from = s[0], to = s[1];
		DFS(a, from, to);
		mp.clear();
	}
}
