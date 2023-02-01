#include<bits/stdc++.h>
using namespace std;

typedef struct LNode
{
	int data;
	int mark;
	struct LNode* next;
}*linklist, LNode;
void Create(linklist &ls,int n)
{
	ls = new LNode;
	ls->next = NULL;
	linklist r = ls;
	for (int i = 0; i < n; i++)
	{
		linklist p = new LNode;
		cin >> p->data;
		p->mark = i + 1;
		p->next = r->next;
		r->next = p;
		r = p;
	}
}
/*
  选择排序

重复（元素个数-1）次

  把第一个没有排序过的元素设置为最小值

  遍历每个没有排序过的元素

    如果元素 < 现在的最小值

      将此元素设置成为新的最小值

  将最小值和第一个没有排序过的位置交换*/
void Sort(linklist& ls,int n)
{
	linklist p = ls->next, q = p->next;
	if (!q||!p)
		return;
	int min = p->data,cnt=0,pos=0;
	for (int i = cnt; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			if (q->data < min)
			{
				min = q->data;
				pos = q->mark;
			}
			q = q->next;
		}

		linklist tp = ls->next;
		for (int k = 1; k < pos; k++)
			tp = tp->next;
		if(pos!=0)
			swap(tp->data, p->data);
		cnt++;
		p = p->next;
		if (p)
		{
			q = p->next;
			min = p->data;
			pos = 0;
		}
		else break;
	}
}
void Show(linklist ls)
{
	linklist p = ls->next;
	while (p->next)
	{
		cout << p->data << ' ';
		p = p->next;
	}
	cout << p->data << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		linklist l;
		Create(l, n);
		Sort(l, n);
		Show(l);
	}
	return 0;
}
