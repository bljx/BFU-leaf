#include<bits/stdc++.h>
using namespace std;

void Find(vector<int>v)
{
	int x;
	cin >> x;

}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		vector<int>v(n+1);
		for (int i = 1; i <= n; i++)
			cin >> v[i];
		int x;
		cin >> x;
		for (int i = 1; i <= n; i++)
		{
			if (v[i] == x)
			{
				cout << i <<" "<< x << endl;
				break;
			}
		}
		vector<int>::iterator it = find(v.begin(), v.end(), x);
		if(it==v.end())
			cout << "not find" << endl;
	}
	return 0;
}
