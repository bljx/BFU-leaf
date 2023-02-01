#include<iostream>
using namespace std;

typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*LinkList;


void CreatList(LinkList &L,int n)
{
	LinkList p;
	if(n==0)
		return ;
	else
	{
		p=new LNode;
		cin>>p->data;
		p->next=NULL;
		L->next=p;
		CreatList(p,n-1);
	}
}
/*
void Output(LinkList L)
{
	LinkList p=L;
	while(p!=NULL)
	{
		cout<<p->data<<endl;
		p=p->next;
	}

}
*/


void Output(LinkList L)
{
	if(L)
	{
		cout<<L->data<<endl;
		Output(L->next);
	}

}

LinkList reverse(LinkList p)
{
	LinkList q,h;
	if(p->next == NULL) return p; // 链表中只有一个结点，逆转后的头指针不变
	else
	{
		q = p->next; // q为链表(a2,an)的头指针
		h = reverse(q); // 逆转链表(a2,an)，并返回逆转后的头指针
		q->next = p; // 将a1联接在a2之后
		p->next = NULL;
		return h; // (a2,,an)逆转表的头指针即为(a1,a2,,an)
	}
}

int main()
{
	LinkList L;
	L=new LNode;
	L->next=NULL;
	cout<<"输入5个数:\n";
	CreatList(L,5);
	Output(L->next);
	return 0;
}