#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

void Create(vector<int>&v,int n)
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		v.push_back(temp);
	}
}
void Find(vector<int> v,int x,int low,int high)
{
	if (low >= high)
	{
		cout << "NO" << endl;
		return;
	}
	int mid = (low + high) / 2;
	if (v[mid] == x)
	{
		cout << "YES" << endl;
		return;
	}
	if (v[mid] < x)
	{
		low = mid + 1;
		Find(v, x, low, high);
	}
	else
	{
		high = mid - 1;
		Find(v, x, low, high);
	}

}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		vector<int> v;
		Create(v, n);
		int x;
		cin >> x;
		int low = 0, high = n - 1;
		Find(v, x,low,high);
	}
	return 0;
}
