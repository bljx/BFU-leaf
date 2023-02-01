#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

vector<int> Sort(vector<int> v)
{
	vector<int> ans(v.size());
	int cnt = 0;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			if (v[j] < v[i])
				cnt++;
		}
		ans[cnt] = v[i];
		cnt = 0;
	}
	return ans;
}
void Show(vector<int> v)
{
	for (int i = 0; i < v.size()-1; i++)
		cout << v[i] << ' ';
	cout << v[v.size() - 1] << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		Show(Sort(v));
	}
	return 0;
}
