#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
int main()//n,n
{
	int n;
	while (cin >> n && n != 0)
	{
		vector<int> v(n);
		vector<int> zheng;
		vector<int> fu;
		for (int i = 0; i < n; i++)
			cin >> v[i];
		for (int i = 0; i < n; i++)
		{
			if (v[i] > 0)
				zheng.push_back(v[i]);
			else if (v[i] < 0)
				fu.push_back(v[i]);
		}
		for (int i = 0; i < zheng.size(); i++)
		{
			if (i != 0)
				cout << " ";
			cout << zheng[i];
		}
		for (int i = 0; i < fu.size(); i++)
			cout << " " << fu[i];
		cout << endl;
	}
	return 0;
}
