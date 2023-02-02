// factorial_loop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream.h>
long factorial(int n)
{
	long l;
	l=1;
	int i;
	for(i=1;i<=n;i++)
	{
		l=l*i;
	}
	return l;
}

int main(int argc, char* argv[])
{
	int n;
	cin>>n;
	cout<<factorial(n)<<endl;
	return 0;
}

