#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
//É¾³ýÖ¸¶¨ÔªËØ
int main()
{
	int n, m;
	cin >> n;
	while (n != 0)
	{
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		cin >> m;
		int j = 0,temp=n;
		for(int i = 0; i < n; i++)
		{
			if (v[i] == m)
				temp--;
		}
		for (int i = 0; i < n; i++)
		{		
			if (v[i] != m)
			{
				cout << v[i];
				j++;
				if (j != temp)
					cout << " ";
			}
		}
		cout << endl;
		cin >> n;
	}
	return 0;
}
