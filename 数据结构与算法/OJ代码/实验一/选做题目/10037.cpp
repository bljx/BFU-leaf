#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	cin >> n;
	while (n != 0)
	{
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		sort(v.begin(), v.end());
		int part = 0, part1 = 0, part2 = 0;
		if (n % 2 == 0)
		{
			part = n / 2;
			for (int i = 0; i < part; i++)
			{
				cout << v[i];
				if (i != part - 1)
					cout << " ";
				if (i == (part - 1))
					cout << endl;
			}
			for (int i = part; i < n; i++)
			{
				cout << v[i];
				if (i != n - 1)
					cout << " ";
			}
			cin >> n;
			if (n != 0)
				cout << endl;
		}
		else
		{
			part1 = n / 2;
			part2 = part1 + 1;
			for (int i = 0; i < part1; i++)
			{
				cout << v[i];
				if (i != part1 - 1)
					cout << " ";
				if (i == part1 - 1)
					cout << endl;
			}
			for (int i = part1; i < n; i++)
			{
				cout << v[i];
				if (i != n - 1)
					cout << " ";
				if (i == n - 1)
					cout << endl;
			}
			cin >> n;
			if (n != 0)
				cout << endl;
		}
	}
	return 0;
}
