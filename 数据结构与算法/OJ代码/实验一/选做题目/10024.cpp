#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int num[100];
int c = 0;
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
void Insert1(linklist &l,int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		num[p->data] =1;
		c++;
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
void Show(linklist l)
{
	linklist p = l;
	while (p)
	{
		cout << p->data << " ";
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
void And(linklist l)
{
	for (int i = 0; i < 100; i++)
	{
		if (num[i] == 2)
			cout << i << " ";
	}
	for (int i = 0; i < 100; i++)
		num[i] = 0;
}
void Insert2(linklist& l, int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		if (num[p->data] == 1)
		{
			c--;
			num[p->data] = 0;
		}
 
		p->next = NULL;
		rear->next = p;
		rear = p;
	}
}
void Minus(linklist l)
{
	linklist p = l->next;
	int i = 0;
	while (p)
	{
		if (num[p->data])
		{
			cout << p->data;
			i++;
			if (i != c)
				cout << " ";
 
		}
		p = p->next;
	}
	cout <<endl << c;
}
int main()
{
	linklist l1,l2;
	Init(l1);
	Init(l2);
	int n1, n2;
	while(cin >> n1 >> n2&&n1!=0&&n2!=0)
	{
		c = 0;
		for (int i = 0; i < 100; i++)
			num[i] = 0;
		Insert1(l1, n1);
		Insert2(l2, n2);
		Minus(l1);
		cout << endl;
 
	}
	return 0;
}

