/***可检测的**关键字**有***  
"int"|"break"|"else"|"switch"|"case"|"char"|"return"|"const"|"for"|"void"|"double"|"if"
*/
//#include<iostream.h>
#include<stdio.h>

void F(){

}

int main()                                                                         
{/*test.c*/
	const int sum1 = 0;
	int sum2=0;
	int  a,b,flag,i;
	double c;
	char str = 'a';
	a = 10;
	b = a + 20; 
	c = 1.2e5;
	c = 1.2E5;
	c = 1.2e-19;
	c = 1.;
	c = .1;
	c = 12.3;
	if(a == b)
		flag = 1;
	else
		flag = 2;
	for(i=1;i<11;i++){
		sum2+=i;
	}
	switch(flag){
		case 1:	
			printf("%d",sum1);
			break;
		case 2: 
			printf("%d",sum2);
			break;
	}	
	return 0;
}//end of program
/**/