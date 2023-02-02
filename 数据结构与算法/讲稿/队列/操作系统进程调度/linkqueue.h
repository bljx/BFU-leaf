#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
//********************PCB定义********************
typedef struct PCB{
	int name;		//用数字对数据块标号
	int state;		//其状态为0或1
	int prior;		//优先级
	int time;		//需要在处理机上执行的时间
}PCB;
//*******************队列的定义*******************
typedef struct QNode{
	PCB   data;
    struct QNode  *next;
}QNode, *QueuePtr;
typedef struct{
    QueuePtr  front;            //队头指针   
    QueuePtr  rear;             //队尾指针
}LinkQueue;  
//********************初始化队列********************
int InitQueue(LinkQueue &Q){
    Q.front=Q.rear=new QNode; 
    if(!Q.front) 
		exit(0);
	Q.front->next=NULL;
    return 1;
}
//********************入队********************
int EnQueue(LinkQueue &Q,PCB e){
	QueuePtr p;
    p=new QNode;
    if(!p) 
		exit(0);
    p->data=e; 
	p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return 1;
}
//********************出队********************
int DeQueue(LinkQueue &Q,PCB &e){
	QueuePtr p;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(Q.front==Q.rear) 
		return 0;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p) 
		Q.rear=Q.front;
    free(p);
    return 1;
}
//********************判断队列是否为空********************
int QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return 0;    
	else
		return 1;
}
