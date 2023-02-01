#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>
using namespace std;
typedef struct LNode
{
	int data;
	LNode* next;
}*linklist, LNode;
vector<int> v;
int emm[100];
int TailInsert(linklist& l, int n)
{
	int cnt = 0;
	v.clear();
	for (int i = 0; i < 100; i++)
		emm[i] = 0;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		vector<int>::iterator it = v.begin();
		it = find(v.begin(), v.end(), abs(temp));
		if (it == v.end()&&emm[abs(temp)]==0)
		{
			emm[abs(temp)] = 1;
			cnt++;
			v.push_back(temp);
		}
	}
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < cnt; i++)
	{
		linklist p = new LNode;
		p->data = v[i];
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
	return cnt;
}
void Show(linklist l,int n)
{
	linklist p = l->next;
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		cout << p->data;
		if (j != n - 1)
		{
			j++;
			cout << " ";
		}
		p = p->next;
	}
	cout << endl;
}
int main()
{
	int n;
	cin >> n;
	while (n)
	{
		linklist l;
		int cnt=TailInsert(l,n);
		Show(l, cnt);
		cin >> n;
	}
	return 0;
}
