#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
class Book
{
public:
	string id, name;
	float price;
};
typedef struct LNode
{
	int data;
	LNode* next;
}*linklist, LNode;
void Init(linklist& l)
{
	l = new LNode;
	l->next = NULL;
}
set<int> s;
void Insert(linklist& l, int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		s.insert(p->data);
		p->next = NULL;
		rear->next = p;
		rear = p;
	}
}
void Show(linklist l, int n)
{
	set<int>::iterator it = s.begin();
	for (int i = 0; i < s.size(); i++)
	{
		cout << *it;
		if (i != s.size()-1)
			cout << " ";
		it++;
	}
	cout << endl;
}
linklist Merge(linklist p1, linklist p2)
{
	if (!p1)
		return p2;
	else if (!p2)
		return p1;
	if (p1->data < p2->data)
	{
		p1->next = Merge(p1->next, p2);
		return p1;
	}
	else if (p1->data > p2->data)
	{
		p2->next = Merge(p1, p2->next);
		return p2;
	}
	else
	{
		p1 = p1->next;
		return p2;
	}
}
int main()
{
	linklist l1, l2;
	Init(l1);
	Init(l2);
	int n1, n2;
	while (cin >> n1 >> n2 && n1 != 0 && n2 != 0)
	{
		Insert(l1, n1);
		Insert(l2, n2);
		linklist ans = Merge(l1->next, l2->next);
		Show(ans, n1 + n2);
		s.clear();
	}
	return 0;
}

