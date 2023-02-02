/****此模板中包含了四个功能：输入、输出、统计个数、排序
     输入Input函数中用到了读文件的语句
	 ifstream inFile("book1.txt"); 此语句打开文件以能读取文件
	 这里要求排序后的结果要写到一个新文件book1_sort.txt中
	 排序Sort函数中用到了写文件的语句
	 ofstream outFile("book1_sort.txt"); 此语句打开文件以能向文件中写入数据
****/


/****我特意为此程序添加了详细的注释
     希望大家搞明白此程序中的每一行代码
	 这些代码是顺序表的基础内容
	 而读写文件后面经常要用到，各种上机考试也经常考到
	 不明白的同学请教下组长
****/

#include <iostream>
#include <fstream>
#include <iomanip>
//#include <string>
using namespace std;


#define SIZE 1000  //用来表示动态数组的大小
int flag=0;      //为使程序具有健壮性，当图书数据输入后flag为1
char BK_head1[10],BK_head2[10],BK_head3[10]; //用来存放文件中图书标题的那一行无用信息


typedef struct {
    char no[15];   
    char name[50]; 
    float price;   
}Book; //图书信息定义


typedef struct{//图书表结构体的定义
    Book *BK;
    int length;//图书表的图书记录个数
}SqList;


void Input(SqList &L){    //从文件book1.txt 中读取图书数据，这里参数一定使用引用，而其他三个函数的参数不需要引用
	int i=0;
    L.BK=new Book[SIZE];  //动态开辟一个数组用以存放图书数据，最多可存储SIZE本图书
	
    ifstream inFile("book1.txt");//注意：你们要读的文件book.txt比book1.txt多出第一行数据：图书个数 105
	if(!inFile)	{   //读取文件失败处理
		cerr<<"Cannot open this file!"<<endl;
		exit(1);
	}
	
	inFile>>BK_head1>>BK_head2>>BK_head3;//读取文件中的标题，即第一行信息：ISBN 书名 定价

	L.length=0; //图书个数初始为0

	while(!inFile.eof()){  //逐行依次读取所有图书数据，直到到达文件尾部
		inFile>>L.BK[i].no >>L.BK[i].name>>L.BK[i].price;
		i++;  //记录图书个数
	}

    L.length=i; //图书个数初始为i

	inFile.close(); //养成一个良好的习惯，文件使用后关闭

	flag=1; //为使程序具有健壮性，图书数据读入后flag为1，当进行其它操作时通过flag可以判断是否已读入数据

	cout<<"\n读取 book.txt 信息完毕，可以通过选项(2)查看图书信息\n"<<endl;
}


void Output(SqList L){   //逐个显示图书信息
	if(flag==0){         //程序健壮性的体现，通过flag判断是否读入图书信息
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}

	cout<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;//输出对齐好看些

	for(int i=1;i<=L.length;i++)
		cout<<left<<setw(15)<<L.BK[i].no <<"\t"<<left<<setw(50)<<L.BK[i].name<<"\t"<<left<<setw(5)<<L.BK[i].price<<endl;
	cout<<"\n信息显示完毕\n"<<endl;
}


void Count(SqList L){        //统计图书个数
	if(flag==0){               //程序健壮性的体现，通过flag判断是否读入图书信息
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}
	cout<<"当前的图书总数为："<<L.length<<endl<<endl;  //L.length的值即为图书个数
}


void Sort(SqList L){ //按价格从低到高排序，排序后的结果写入文件book1_sort.txt
	Book b;
	if(flag==0){    //程序健壮性的体现，通过flag判断是否读入图书信息
		cout<<"还没有从book.txt中读取图书信息，请选择(1)输入图书信息\n"<<endl;
		return;
	}
	cout<<"所有图书按价格由低到高排序后存在book_sort.txt中"<<endl;
	for(int i=0;i<L.length;i++){                  //冒泡排序
		for(int j=0;j<L.length-i-1;j++){
			if(L.BK[j].price>L.BK[j+1].price){
				b=L.BK[j];
				L.BK[j]=L.BK[j+1];
				L.BK[j+1]=b;
			}
		}
	}
	ofstream outFile("book1_sort.txt"); //打开文件以能向文件中写入数据

	outFile<<left<<setw(15)<<BK_head1<<"\t"<<left<<setw(50)<<BK_head2<<"\t"<<left<<setw(5)<<BK_head3<<endl;//写入标题
	for(i=0;i<=L.length-1;i++) //逐行写入图书信息
		outFile<<left<<setw(15)<<L.BK[i].no<<"\t"<<left<<setw(50)<<L.BK[i].name<<"\t"<<left<<setw(5)<<L.BK[i].price<<endl;
}


void main(){
	char no;
	SqList L;

	while(1)
	{
		cout<<"**************************** 欢学使用图书信息管理系统！*************************"<<"\n";//菜单选项
		cout<<"(1)输入图书信息"<<endl;
		cout<<"(2)逐个显示图书信息"<<endl;
		cout<<"(3)统计表中图书个数"<<endl;
		cout<<"(4)将所有图书按价格排序"<<endl;
		cout<<"(0)退出系统"<<endl;
		cout<<endl;
		cout<<"请选择您需要的服务:";
		cin>>no;
		switch(no){
		case '1':
			Input(L);break;
		case '2':
			Output(L);break;
	    case '3':
			Count(L);break;
        case '4':
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

