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
		
		//赋值 
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
 
void FindFavouriteBooks(LinkList &L)
{
	//用数组存储待查找书名
	string bookname[10];
	//找到的书，存在fav数组中
	LinkList favouritebooks[5]; 
	
	//查找n个目标 
	int n;
	cin>>n;
	
	for(int i=0;i<n;i++)
	{
		cin>>bookname[i];
	}
	
	//遍历指针 
	LinkList p;
	//计数器k:记录找到的书的数目
	int k=0;
	for(int j=0;j<n;j++)
	{ 
		//初始化查找到的书的数目 
		k=0;
		//跳过头节点开始遍历 
		p=L->next;
		while(p)
		{
			if(p->data.name==bookname[j])
			{
				favouritebooks[k]=p;//成功比对，查找到的目标元素的地址存在favouritebooks数组中 
				k++;
			}			
			p=p->next;
		}
		if(k==0)
			cout<<"Sorry，there is no your favourite!"<<endl;
		else
		{
			cout<<k<<endl;
			for(int i=0;i<k;i++)
				cout<<favouritebooks[i]->data.no<<" "<<favouritebooks[i]->data.name<<" "<<setiosflags(ios::fixed)<<setprecision(2)<<favouritebooks[i]->data.price<<endl;
		}
	}
	
}
 
int main()
{
	LinkList L;
	CreateList_R(L);
	FindFavouriteBooks(L); 
	return 0;
}

