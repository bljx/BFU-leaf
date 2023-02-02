#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;


typedef struct {
    char no[15];   
    char name[50]; 
    float price;   
}Book; //图书信息定义


typedef struct LNode{
	Book   data;       //数据域
	struct LNode  *next;   //指针域
}LNode,*LinkList; 

int num=0;//记录图书个数
char BK_head1[10],BK_head2[10],BK_head3[10];

void Input(LinkList &L){     //从book.txt 中读取信息，后插法创建图书链表
	LinkList p,r;
	
	L=new LNode;
	L->next=NULL;//初始化单链表
	
	r=L;
	
	ifstream inFile("book.txt");
	if(!inFile){
		cerr<<"Cannot open this file!"<<endl;
		exit(1);
	}
	
	inFile>>BK_head1>>BK_head2>>BK_head3;//读取文件中的标题
	num=0;
	while(!inFile.eof()){    //逐行依次读取所有图书数据
		p=new LNode;  //生成新结点
		inFile>>p->data.no>>p->data.name>>p->data.price;
		p->next=NULL;
		r->next=p;  //插入到表尾
		r=p;
		num++;   //记录图书个数
	}

	inFile.close();
	cout<<"文件读取完毕"<<endl;
		
    inFile.close();
	cout<<"\n读取 book.txt 信息完毕，可以通过选项(2)查看图书生信息\n"<<endl;
}

void Output(LinkList L){  //逐个显示表中的信息
	if(num==0) {      //判断是否读入图书信息
	    cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	LinkList p;
	p=L->next;
	/*for(int i=0;i<num;i++){
		cout<<p->data.no<<"\t"<<p->data.name<<"\t"<<p->data.score<<endl;
		p=p->next;
	}*/
	
	cout<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<setw(5)<<BK_head1<<endl;
	while(p){     //循环输出图书信息
		cout<<left<<setw(15)<<p->data.no<<"\t"<<left<<setw(50)<<p->data.name<<"\t"<<left<<setw(5)<<p->data.price<<endl;
		p=p->next;
	}	
	cout<<"\n信息显示完毕\n"<<endl;
}

void Count_Len(LinkList L){
	if(num==0){    //判断是否读入图书信息     
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	cout<<"当前的图书总数为："<<num<<endl<<endl;
}


void NameSearch(LinkList L){          //按书名查找图书信息  
	if(num==0){      //判断是否读入图书信息                                
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	char n[30];
	cout<<"请输入您要查找的书名：";
	cin>>n;                 //输入要查找的书的名称
	int a=0;
	LinkList p;
	p=L->next;
	while(p){      
		if(strcmp(n,p->data.name)==0){      //用strcmp()函数判断是否有要查找的书  
			if(a==0){
				cout<<"找到该书，该书的信息如下："<<endl;
				cout<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;
			}
			cout<<left<<setw(15)<<p->data.no<<"\t"<<left<<setw(50)<<p->data.name<<"\t"<<left<<setw(5)<<p->data.price<<endl;  //输出找到书的信息
			a++;
		}
		p=p->next;
	}
	if(a==0)
		cout<<"对不起，没有您要查找的书!"<<endl;
}

   
void LocationSearch(LinkList L){    //按位置查找图书信息
	if(num==0){      //判断是否读入图书信息	                                    
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	int i;     //i用于记录要查找图书的位置
	cout<<"请输入您要查找的图书的位置：";
	cin>>i;
	LinkList p;
	int j;
	p=L->next;
	j=1;
	while(p&&j<i){    //循环找到图书的位置
		p=p->next;
		++j;
	}
	if(!p||j>i){
		cout<<"您要查找的元素不存在"<<endl;
		return;
	}
	cout<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;
	cout<<left<<setw(15)<<p->data.no<<"\t"<<left<<setw(50)<<p->data.name<<"\t"<<left<<setw(5)<<p->data.price<<endl;
}


void Insert(LinkList L){
	if(num==0){       //判断是否读入图书信息	                                   
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	int i;    //i用于记录要插入图书的位置
	cout<<"请输入您要插入图书的位置：";
	cin>>i;
	LinkList p,l;
	int j;
	p=L;
	j=0;
	while(p&&j<i-1){       //循环找到要插入图书的位置
		p=p->next;
		++j;
	}
	if(!p||j>i-1){
		cout<<"您要插入图书的位置不正确"<<endl;
		return;
	}
	LinkList s=new LNode;
	cout<<"请输入您要插入图书的信息(包括编号、书名和定价)：";
	cin>>s->data.no>>s->data.name>>s->data.price;     //输入插入图书的信息
	s->next=p->next;
	p->next=s;
	++num;

	l=L->next;
	int k;
	ofstream outFile("book.txt");       //插入图书后用while循环重写入"book.txt"
	outFile<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;
	for(k=1;k<num;k++){	
		outFile<<left<<setw(15)<<l->data.no<<"\t"<<left<<setw(50)<<l->data.name<<"\t"<<left<<setw(5)<<l->data.price<<endl;
		l=l->next;
	}
	outFile<<left<<setw(15)<<l->data.no<<"\t"<<left<<setw(50)<<l->data.name<<"\t"<<left<<setw(5)<<l->data.price;   //最后一行输入不换行
	cout<<"插入图书后重写入“book.txt”中"<<endl;
}


void Delete(LinkList L){
	if(num==0){       //判断是否读入图书信息	                                   
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	int i;    //i用于记录要删除图书的位置
	cout<<"请输入您要删除图书的位置：";
	cin>>i;
	LinkList p,q,l;
	int j;
	p=L;
	j=0;
	while(p->next&&j<i-1){       //循环找到要删除图书的位置
		p=p->next;
		++j;
	}
	if(!(p->next)||j>i-1){
		cout<<"您要删除图书的位置不正确"<<endl;
		return;
	}
	q=p->next;
	p->next=q->next;
	delete q;
	--num;

	l=L->next;
	int k;
	ofstream outFile("book.txt");       //删除图书后用while循环重写入"book.txt"
	outFile<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;
	for(k=1;k<num;k++){
		outFile<<left<<setw(15)<<l->data.no<<"\t"<<left<<setw(50)<<l->data.name<<"\t"<<left<<setw(5)<<l->data.price<<endl;
		l=l->next;
	}
	outFile<<left<<setw(15)<<l->data.no<<"\t"<<left<<setw(50)<<l->data.name<<"\t"<<left<<setw(5)<<l->data.price;    //最后一行输入不换行
	cout<<"删除图书后重写入“book.txt”中"<<endl;
}


void Sort(LinkList L){     //按价格从低到高排序                       
	if(num==0){      //判断是否读入图书信息	              
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}
	

	LinkList p,pnext,q,l;
    int i,j;
	for(i=0;i<num-1;i++){          //冒泡排序
        q=L;
        p=L->next;
        pnext=p->next;
        for(j=0;j<num-i-1;j++){
            if(p->data.price>pnext->data.price){
                p->next=pnext->next;
                q->next=pnext;
                q=pnext;
                q->next=p;
            }
            else{           
                q=q->next;
                p=p->next;
            }
            pnext=p->next;
        }
    }

	l=L->next;
	ofstream outFile("book_sort.txt");       //将排序后的图书信息用while循环写入名为"book_sort.txt"的文件中
	outFile<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;
	while(l){
		outFile<<left<<setw(15)<<l->data.no<<"\t"<<left<<setw(50)<<l->data.name<<"\t"<<left<<setw(5)<<l->data.price<<endl;
		l=l->next;
	}
	cout<<"所有书按价格由低到高排序后存在“book_sort”中。"<<endl;
}


int main(){
	char no;
	LinkList L;

	while(1){
		cout<<"**************************** 欢学使用图书信息管理系统！*************************"<<"\n";//菜单选项
		cout<<"(1)输入图书信息"<<"\n";
		cout<<"(2)逐个显示图书信息"<<"\n";
		cout<<"(3)统计表中图书个数"<<"\n";
		cout<<"(4)根据书名进行查找"<<"\n";
		cout<<"(5)根据指定位置进行查找"<<"\n";
		cout<<"(6)插入图书信息到指定位置"<<"\n";
		cout<<"(7)删除指定位置的图书记录""\n";
		cout<<"(8)将所有图书按价格排序""\n";
		cout<<"(0)退出系统"<<"\n";
		cout<<"\n";
		cout<<"请选择您需要的服务:";
		cin>>no;
		switch(no){
		case '1':
			Input(L);break;
		case '2':
			Output(L);break;
        case '3':
			Count_Len(L);break;
		case '4':
			NameSearch(L);break;
		case '5':
			LocationSearch(L);break;
        case '6':
			Insert(L);break;
		case '7':
			Delete(L);break;
		case '8':
			Sort(L);break;
		case '0':
			cout<<"欢迎再次使用~bye bye~"<<endl;
			exit(0);
		default :
			cout<<"请选择正确的操作！！"<<endl;
			break;
		}
	}
}
