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
	Book data;
	LNode* next;
}*linklist, LNode;
void Init(linklist &l)
{
	l = new LNode;
	l->next = NULL;
}
void Change(linklist& l, float avg)
{
	linklist p = l->next;
	while (p)
	{
		if (p->data.price < avg)
			p->data.price *= 1.2;
		else
			p->data.price *= 1.1;
		p = p->next;
	}
}
void Insert(linklist &l,int n)
{
	l = new LNode;
	l->next = NULL;
	linklist rear = l;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data.id >> p->data.name >> p->data.price;
		p->next = NULL;
		rear->next = p;
		rear = p;
	}
}
void Sort(linklist& l, int n)
{
	linklist p = l;
	for (int i = 0; i < n; i++)
	{
		p = l->next;
		int j = 0;
		while (p && j < n - 1 - i)
		{
			if (p->data.price < p->next->data.price)
			{
				Book t = p->data;
				p->data = p->next->data;
				p->next->data = t;
			}
			p = p->next;
			j++;
		}
	}
}
void ShowMaxPrice(linklist l , int maxprice)
{
	linklist p = l->next;
	int cnt = 0;
		while(p->data.price == maxprice)
		{
			cnt++;
			p = p->next;
		}	
	cout << cnt << endl;
	delete p;
	linklist q = l->next;
	while (q->data.price == maxprice)
	{
		printf("%s %s %.2f\n", q->data.id.c_str(), q->data.name.c_str(), q->data.price);
		q = q->next;
	}
}
void HeadInsert(linklist& l,int n)//是倒序！！
{
	l = new LNode;
	l->next = NULL;
	for (int i = 0; i < n; i++)
	{
		linklist q = new LNode; 
		cin >> q->data.id >> q->data.name >> q->data.price;
		q->next = l->next;         //尾指针为0
		l->next = q;            //将q插在p的后面
	}
}
 
void Show(linklist l)
{
	linklist p = l->next;
	while (p)
	{
		printf("%s %s %.2f\n", p->data.id.c_str(), p->data.name.c_str(), p->data.price);
		p = p->next;
	}
}
vector<string> v;
void Find(linklist l,string s)
{
	vector<string>::iterator it=find(v.begin(),v.end(),s);
	if (it == v.end())
	{
		cout << "Sorry，there is no your favourite!" << endl;
		return;
	}
	linklist p = l->next;
	while (p)
	{
		if(p->data.name==s)
			printf("%s %s %.2f\n", p->data.id.c_str(), p->data.name.c_str(), p->data.price);
		p = p->next;
	}
}
void LoveBook(linklist l, int n,int m)
{
	linklist p = l->next;
	int i = 1;
	while (p&&i<=n)
	{
		if (i == m)
		{
			printf("%s %s %.2f\n", p->data.id.c_str(), p->data.name.c_str(), p->data.price);
			break;
		}
		p = p->next;
		i++;
	}
}
void In(linklist& l, int n,int m)
{
	linklist p = new LNode, q = l->next;
	int j = 1;
	while (q&&j<m-1)
	{
		j++;
		q = q->next;
	}
	cin >> p->data.id >> p->data.name >> p->data.price;
	p->next = q->next;
	q->next = p;
}
int main()
{
	linklist l;
	Init(l);
	int cnt,cnt2;
	cin >> cnt;
	Insert(l, cnt);
	//HeadInsert(l,cnt);
	cin >> cnt2;
	if (cnt2 > cnt)
		cout << "Sorry，the position to be inserted is invalid!" << endl;
	else
	{
		In(l, cnt, cnt2);
		Show(l);
	}
	return 0;
}

