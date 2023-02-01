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
	string data;
	LNode* next;
	LNode* prior;
}*linklist, LNode;
void TInsert(linklist& l, int n)
{
	l = new LNode;
	l->next = NULL;
	cin >> l->data;
	linklist head = l;
	for (int i = 1; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		p->next = head;
		head->prior = p;
		head = p;
	}
	l->next = head;
	head->prior = l;
}
void Find(linklist l1, linklist l2)
{
	while (l1 && l2)
	{
		string temp = l1->data == l2->data ? l1->data :l1->prior->data;
		if ((l1->data != l2->data) || (l1->next == l1 && l2->next == l2))
		{
			cout << temp << endl;
			break;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
}
int main()
{
	int n1,n2;
	cin >> n1>>n2 ;
	while (n1&&n2)
	{
		linklist s1,s2;
		TInsert(s1,n1);
		TInsert(s2, n2);
		Find(s1->next, s2->next);
		cin >> n1 >> n2;
	}
	return 0;
}
