
//打开工程，依次操作菜单如下：Project->Setting->Link，在Category 中选中Output，然后在Reserve中设定堆栈的最大值和commit。 

//注意：reserve最小值为4Byte；commit是保留在虚拟内存的页文件 



#include<iostream.h>
int x=0;
double factorial(int n)
{
	if(n==1)
		return 1;
	else
	{
		cout<<++x<<endl;
		return n*factorial(n-1);}
}

int main(int argc, char* argv[])
{
	int n;
	cin>>n;
	cout<<factorial(n)<<endl;
	return 0;
}

