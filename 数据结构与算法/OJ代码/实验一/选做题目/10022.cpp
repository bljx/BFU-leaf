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
void Init(linklist &l)
{
	l = new LNode;
	l->next = NULL;
}
void Insert(linklist &l,int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		p->next = NULL;
		rear->next = p;
        rear = p;
	}
}
void HeadInsert(linklist& l,int n)//ÊÇµ¹Ðò£¡£¡
{
	l = new LNode;
	l->next = NULL;
}
 
void Show(linklist l,int n)
{
	linklist p = l;
	int i=0;
	while (p)
	{
		i++;
		cout << p->data;
		if(i!=n)
			cout<<" ";
		p = p->next;
	}
}
linklist Merge(linklist p1, linklist p2)
{
	if (!p1)
		return p2;
	else if (!p2)
		return p1;
	if (p1->data < p2->data)
	{
		p1->next=Merge(p1->next, p2);
		return p1;
	}
	else// if (p1->data > p2->data)
	{
		p2->next=Merge(p1, p2->next);
		return p2;
	}

}
linklist Reverse(linklist l)
{
	linklist p = l, l1;
	l1 = new LNode;
	l1->data = l->data;
	l1->next = NULL;
	while (p)
	{
		linklist q;
		q = new LNode;
		q->data = p->data;
		q->next = l1->next;
		l1->next = q;
		p = p->next;
	}
	return l1;
}
int main()
{
	linklist l1,l2;
	Init(l1);
	Init(l2);
	int n1, n2;
	while(cin >> n1 >> n2&&n1!=0&&n2!=0)
	{
		Insert(l1, n1);
		Insert(l2, n2);
		linklist ans=Merge(l1->next, l2->next);
		Show(Reverse(ans)->next,n1+n2);
		cout << endl;
	}
 
	return 0;
}
