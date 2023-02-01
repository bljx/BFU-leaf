#include <iostream>
#include<iomanip>
using namespace std;
#define MAXSIZE 10000
 
typedef struct 
{
	string no;
	string name;
	double price;
}Book;
 
typedef struct LNode
{
	Book data;
	struct LNode *next;
}LNode,*LinkList;
 
void CreateList_R(LinkList &L)
{
	//尾指针rear 
	LinkList r; 
	//新节点指针p 
	LinkList p;
	
	//创建头节点并初始化其指针域为空 
	L=new LNode;
	L->next=NULL;
	
	//初始，尾指针指向头节点 
	r=L;
	
	int n;
	cin>>n;
	
	int i=0;
	while(1) 
	{
		//新节点指针负责创建新节点 
		p=new LNode;
		//新节点（p）初始化 ：指向空 
		p->next=NULL;
		
		
		string a,b;
		double c;
		cin>>a>>b>>c;
		p->data.no=a;
		p->data.name=b;
		p->data.price=c; 
		
		//尾指针指向的节点（r->next）指向新节点（p） 
		r->next=p;
		//尾指针（r）指向新节点 （p） 
		r=p;
		
		i++;
		if(i==n) break;
	}
	return;
}
 
void FindMostExpensiveBooks(LinkList &L)
{
	LinkList p;
	//越过头节点，从第一个节点开始 
	p=L->next;
	//一个最大节点 
	LinkList max=p;
	//多个相同值的最大节点 
	LinkList maxs[3];//使用没有初始化的指针将发生无法预料的结果
	
	//遍历链表 
	while(p)
	{
		//链表中所有节点依次与最大节点打擂台 
		if(p->data.price > max->data.price)
		{
			//用最大节点指针保存一个最大节点的地址 
			max=p;
		}
		//遍历下一个节点 
		p=p->next;
	}
	
	//越过头节点，从第一个节点开始 
	p=L->next;
	//最大节点数统计 
	int k=0;
	//遍历链表	
	while(p)	
	{
		//链表中如果有等于最大节点的其他节点 
		if(p->data.price==max->data.price)
		{
			//存入最大节点数组 
			maxs[k]=p;
			k++;
		}
		//遍历下一个节点 
		p=p->next;
	}
	
	cout<<k<<endl;
	int i=0;
	while(maxs[i]&&i<k)
	{
		cout<<maxs[i]->data.no<<" "<<maxs[i]->data.name<<" ";
		cout<<fixed<<setprecision(2)<<maxs[i]->data.price<<endl;
		i++;
	}
 
}
 
int main()
{
	LinkList L;
	CreateList_R(L);
	FindMostExpensiveBooks(L);
	return 0;
}

