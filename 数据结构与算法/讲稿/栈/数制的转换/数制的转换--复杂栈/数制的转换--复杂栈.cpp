 #include<iostream.h>
 #include<stdio.h> 
 #include<stdlib.h> 
 #include<math.h> 

 typedef int SElemType; 

 #include"stack.h" 

void conversion ( ) {
  //对于输入的任意一个非负十进制数，打印输出与其等值的二进制数
  SqStack S;
  int N,e;
  InitStack(S);      //构造空栈
  cin>>N;
  while(N) {
    Push(S,N%2);
    N=N/2;
  }
  while (!StackEmpty(S)){
    Pop(S,e);
    cout<<e;
  }
}// conversion

 void main() 
 {
   cout<<"请输入一个十进制数："<<endl;
   conversion ( ) ;
   cout<<endl;
 }

