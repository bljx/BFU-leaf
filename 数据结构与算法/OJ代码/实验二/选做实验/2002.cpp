#include<iostream>
#include<string>
#include<algorithm>// n,1
using namespace std;
typedef struct
{
	int top[2], bot[2];                         //栈顶和栈底指针
	int* V;                                     //栈数组
	int m;                                    //栈最大可容纳元素个数
}DStack;
void Init(DStack& ds,int n)
{
	ds.V = new int[n];
	ds.top[0] = -1;
	ds.top[1] = n;
	ds.bot[0] = -1;
	ds.bot[1] = n;
}
void Insert(DStack& ds,int n1,int n2)
{
	for (int i = 0; i < n1; i++)
		cin >> ds.V[++ds.top[0]];
	for (int i = 0; i < n2; i++)
		cin >> ds.V[--ds.top[1]];
}
void Out(DStack& ds,int n,int i1,int o1,int i2,int o2)
{
	for (int i = 0; i < o1; i++)
	{
		if (i != 0)  cout << " ";
		cout << ds.V[ds.top[0]--];
	}
	if (o1 < i1)   cout << " 1" << endl;
	else   cout << " 0" << endl;
	for (int i = 0; i < o2; i++)
	{
		if (i != 0)  cout << " ";
		cout << ds.V[ds.top[1]++];
	}
	if (o2 < i2)  cout << " 1" << endl;
	else   cout << " 0" << endl;
}
void Full(int n,int i1,int i2)
{
	if (i1 + i2 == n)   cout << 1 << endl;
	else   cout << 0 << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		DStack ds;
		Init(ds, n);
		int i1, i2,o1,o2;
		cin >> i1 >> i2>> o1 >> o2;
		Full(n, i1, i2);
		Insert(ds,i1, i2);
		Out(ds, n, i1, o1, i2, o2);
	}
	return 0;
}
