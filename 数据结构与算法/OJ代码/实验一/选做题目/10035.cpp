#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int main()
{
	int n,m;
	cin >> n;
	while (n!=0)
	{
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		cin >> m;
		int mov = m % n;
		for (int i = mov; i < n; i++)
			cout << v[i]<<" ";
		for (int i = 0; i < mov; i++)
		{
			cout << v[i];
			if(i!=mov-1)
				cout<<" ";
		}
		cout << endl;
		cin >> n;
	}
	return 0;
}
