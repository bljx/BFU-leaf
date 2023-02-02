#include <iostream>
using namespace std;

int s[100],top=0;

void Push(int s[],int x){
	s[top]=x;
	top++;
}

void Pop(int s[],int &x){
	top--;
	x=s[top];
}

int StackEmpty(int s[]){
	if(top==0) return 1;
	else return 0;
}

void conversion () {
	//InitStack(S);      //¹¹Ôì¿ÕÕ»
    int N,e;
    cin>>N;
    while(N) {
		Push(s,N%2);
	    N=N/2;
  }
  while (!StackEmpty(s)){
	  Pop(s,e);
	  cout<<e;
  }
}


int main ( ) {
	 conversion();
	 return 1;
}


