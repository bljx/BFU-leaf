// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

template <class T,int N>
 T max(T arr[N])
{
	T m;
	m = arr[0];
	for (int i = 1; i < N; i++)
	{
		if (arr[i] > m)
			m = arr[i];
	}
	return m;
}

int main()
{
	int a[5] = { 34,-348,3838,695,12 };
	cout << max<int, 5>(a) << endl;
	double b[6] = { 34.27,359.59,495,-458.34,283,-31.23 };
	cout << max<double, 6>(b) << endl;
    return 0;
}
