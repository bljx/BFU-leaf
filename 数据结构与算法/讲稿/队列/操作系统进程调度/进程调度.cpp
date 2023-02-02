#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include"linkqueue.h"
//****************输出就绪队列和等待队列中的进程****************
void Print(LinkQueue &wait,LinkQueue &ok){
	QueuePtr p;

	if(QueueEmpty(ok)){		//若就绪队列不为空，则输出就绪队列
		p=ok.front->next;	//将p指向ok首元素
		cout<<"就绪队列为：";
		while(p!=NULL){
			cout<<p->data.name<<"   ";
			p=p->next;
		}
	}
	else
		cout<<endl<<"无进程在就绪队列";

	if(QueueEmpty(wait)){	//若等待队列不为空，则输出就绪队列
		p=wait.front->next;//将p指向wait首元素
		cout<<endl<<"等待队列为：";
		while(p!=NULL){
			cout<<p->data.name<<"   ";
			p=p->next;
		}
	}
	else 
		cout<<endl<<"无进程在等待队列";
}
//*********************先进先出调度算法*********************
void FCFS(LinkQueue &wait,LinkQueue &ok){//wait为等待对列，ok为就绪队列
	int i=1;
	PCB e,f;

	Print(wait,ok);

	while(QueueEmpty(wait)&&QueueEmpty(ok)){		
		cout<<endl<<"第"<<i<<"步------";
		int j=rand()%3;//产生随机数0，1，2		
		if(j==0){
			DeQueue (ok,e);//从就绪队列中出来
			cout<<"进程"<<e.name<<"执行完毕,生成随机数0,不再执行"<<endl;
		}
		else if(j==1){
			DeQueue (ok,e);//从就绪队列中出来
			EnQueue (ok,e);//插入就绪队列的队尾
			cout<<"进程"<<e.name<<"执行完毕,生成随机数1,插入就绪队列的队尾"<<endl;
		}
		else if(j==2){
			DeQueue (ok,e);//从就绪队列中出来
			EnQueue (wait,e);//插入等待队列
			DeQueue(wait,f);//从等待队列中出来
			EnQueue(ok,f);//插入就绪队列
			cout<<"进程"<<e.name<<"执行完毕,生成随机数2,插入等待队列的队尾，同时将等待队列中的第一个进程插入就绪队列的队尾"<<endl;
		}

		Print(wait,ok);

		i++;
	}
}
//********************按优先级由大到小对队列排序********************
void Findprior(LinkQueue &Q){
	PCB temp;		//中间变量
	QueuePtr p,q,large;
	p=new QNode;
	q=new QNode;
	large=new QNode;
	p=Q.front->next;
	for(p;p->next!=NULL;p=p->next){
		large=p; 
		for(q=p->next;q;q=q->next) 
			if(q->data.prior>large->data.prior) 
				large=q; 
		if(large!=p){
			temp=p->data; 
			p->data=large->data; 
			large->data=temp;
		} 
	}
}
//********************基于优先级的调度算法********************
void Prior(LinkQueue &wait,LinkQueue &ok){
	int i=1;
	PCB e,f;
	
	Print(wait,ok);

	while(QueueEmpty(wait)&&QueueEmpty(ok)){		
		cout<<endl<<"第"<<i<<"步------";
		Findprior(ok);
		int j=rand()%3;//产生随机数0，1，2		
		if(j==0){
			DeQueue (ok,e);
			cout<<"进程"<<e.name<<"优先级最高为"<<e.prior<<"率先执行,执行完毕,生成随机数0,不再执行"<<endl;
		}
		else if(j==1){
			DeQueue (ok,e);
			EnQueue (ok,e);
			cout<<"进程"<<e.name<<"优先级最高为"<<e.prior<<"率先执行,执行完毕，生成随机数1,插入就绪队列的队尾"<<endl;
		}
		else if(j==2){
			DeQueue (ok,e);
			EnQueue (wait,e);
			DeQueue(wait,f);
			EnQueue(ok,f);		
			cout<<"进程"<<e.name<<"优先级最高为"<<e.prior<<"率先执行,执行完毕,生成随机数2,插入等待队列的队尾，同时将等待队列中的第一个进程插入就绪队列的队尾"<<endl;
		}
		
		Print(wait,ok);

		i++;
	}
}
//********************按执行时间由小到大对队列排序********************
void Findsjf(LinkQueue &Q){
	PCB temp;
	QueuePtr p,q,small;
	p=new QNode;
	q=new QNode;
	small=new QNode;
	p=Q.front->next;
	for(p;p->next!=NULL;p=p->next){
		small=p; 
		for(q=p->next;q;q=q->next) 
			if(q->data.time<small->data.time) 
				small=q; 
		if(small!=p){
			temp=p->data; 
			p->data=small->data; 
			small->data=temp;
		} 
	}
}
//***************最短执行时间调度算法***************
void SJF(LinkQueue &wait,LinkQueue &ok){
	int i=1;
	PCB e,f;

	Print(wait,ok);

	while(QueueEmpty(wait)&&QueueEmpty(ok)){		
		cout<<endl<<"第"<<i<<"步------";
		Findsjf(ok);
		int j=rand()%3;//产生随机数0，1，2		
		if(j==0){
			DeQueue (ok,e);
			cout<<"进程"<<e.name<<"执行时间最短为"<<e.time<<"率先执行,执行完毕,生成随机数0,不再执行"<<endl;
		}
		else if(j==1){
			DeQueue (ok,e);
			EnQueue (ok,e);
			cout<<"进程"<<e.name<<"执行时间最短为"<<e.time<<"率先执行,执行完毕，生成随机数1,插入就绪队列的队尾"<<endl;
		}
		else if(j==2){
			DeQueue (ok,e);
			EnQueue (wait,e);
			DeQueue(wait,f);
			EnQueue(ok,f);		
			cout<<"进程"<<e.name<<"执行时间最短为"<<e.time<<"率先执行,执行完毕,生成随机数2,插入等待队列的队尾，同时将等待队列中的第一个进程插入就绪队列的队尾"<<endl;
		}

		Print(wait,ok);

		i++;
	}
}
void main(){
	int i;
	char c,b;
	LinkQueue wait,ok;	//定义等待队列和就绪队列
	do{
		system("cls");	//清屏
		cout<<"****************欢迎使用进程调度系统****************"<<endl;
		InitQueue(ok);	//初始化等待队列和就绪队列
		InitQueue(wait);
		for(i=0;i<10;i++){
			PCB p;
			p.name=i+1;
			p.prior=rand()%10;	//产生随机数0-9,作为优先级
			p.state=rand()%2;	//产生随机数0和1,若为1则就绪,若为0则等待
			p.time=rand()%100;
			if(p.state) 
				EnQueue(ok,p);	//1的话进入就绪队列
			else 
				EnQueue(wait,p);//0的话进入等待队列
			
			cout<<"进程名"<<"\t"<<p.name<<"\t";	
			cout<<"优先级:"<<p.prior<<"\t";
			if(p.state)	
				cout<<"就绪"<<"  "<<"\t";
			else 
				cout<<"等待"<<"  "<<"\t";
			cout<<"执行时间"<<p.time<<"ms"<<endl;
		}
		cout<<endl<<endl;
		cout<<"****************************************************"<<endl;
		cout<<"* 就绪和等待队列已经生成,请选择您希望的调度算法: ***"<<endl;
		cout<<"* 1.先进先出调度算法********************************"<<endl;
		cout<<"* 2.基于优先级的调度算法****************************"<<endl;
		cout<<"* 3.最短执行时间调度算法****************************"<<endl;
		cout<<"* 0.退出********************************************"<<endl;
		cout<<"****************************************************"<<endl;
		cout<<"请输入数字（0-3）:";
		cin>>b;
		switch(b){
			case '1':
				FCFS(wait,ok);
				break;
			case '2':
				Prior(wait,ok);
				break;
			case '3':
				SJF(wait,ok);
				break;
			case '0':
				cout<<"感谢您的使用!"<<endl;
				exit(0);
			default:
				cout<<"您输入的代号有误,请重新输入";
		}
		cout<<endl<<endl<<"还要继续么？（Y/N）"<<endl;
		cin>>c;
	}while(c=='Y'||c=='y');
	cout<<"感谢您的使用!"<<endl;
	exit(0);
}
