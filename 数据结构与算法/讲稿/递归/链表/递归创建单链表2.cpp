#include<iostream.h>

typedef struct LNode{
		 int data;
 struct LNode *next;}LNode,*LinkList;
/*void CreatList(LinkList &L){
	int i,n;LinkList p;
	L=new LNode;
	L->next=NULL;
	cin>>n; //输入待建链表中元素的个数	
	for(i=0;i<n;i++){
		p= new LNode;
		cin>>p->data.name>>p->data.price;      //逐个输入图书信息
		p->next=L->next; L->next=p;       }    //插入到表头	
}*/

void CreatList(LinkList &p){
	int n;
	cin>>n; //输入结点数值，输入0则退出
	if (n==0)  p=NULL;
    else{
		p=new LNode;
		p->data=n;
		CreatList(p->next);
	}
}

void Output(LinkList &p){
	if (p==NULL) return;
    else{
		cout<<p->data<<' ';
		Output(p->next);
	}
}

/*
 LNode* node = (LNode *) malloc (sizeof(LNode));//申请新节点
 L.next = node;    //指针连接
 node ->data = n;   //数据组装
 node ->next = NULL;   //尾节点赋空

 create(L, n);    //继续递归
}
*/
void Min (LinkList L ){
	LinkList pmin,p;
	if(L->next==NULL) return ;
	pmin=L->next; 	p=L->next->next;
	while(p != NULL ){
		if(p->data<pmin->data) pmin=p;
		p=p->next;	}
   cout<<"最便宜的图书是:"<<pmin->data<<endl; 	
}
void main( ){	  
	  LinkList  L;
	  L=new LNode;
	  L->next=NULL;
	  CreatList(L->next);//创建新链表	  
	  Output(L->next);
	  Min(L);   //输出最便宜的图书
 }