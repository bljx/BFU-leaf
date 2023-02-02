#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;
//4025 Ë«Ö¸Õë
void Create(vector<int>&v,int n)
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		v.push_back(temp);
	}
}
void Sort(vector<int>&v,int n)
{
	int i = 0, j = n-1;//iÕý£¬j¸º
	while (i!=j)
	{
		while (v[i] < 0)
			i++;
		while (v[j] > 0)
			j--;
		if (i == v.size()-1||j==0)
			break;
		int temp;
		temp = v[i];
		v[i] = v[j];
		v[j] = temp;
		i++;
		j--;
	}
}
void Print(vector<int> v)
{
	for (int i=0;i<v.size()-1;i++)
			cout << v[i] << ' ';
	cout << v[v.size()-1] << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		vector<int> v;
		Create(v, n);
		Sort(v,n);
		Print(v);
	}
	return 0;
}
