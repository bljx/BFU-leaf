#include<iostream>
#include<set>
using namespace std;
int main()
{//m*n,m*n 
	int m, n;
	while (cin >> m >> n && m != 0 && n != 0)
	{
		int flag = 0;
		set<int> s;
		set<int>::iterator it = s.begin();
		for (int i = 0; i < m * n; i++)
		{
			int t;
			cin >> t;
			it = s.find(t);
			if (it == s.end())//找不到，说明和之前的不重复
				s.insert(t);
			else
				flag = 1;
		}
		if (flag == 0)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
		s.clear();
	}
	return 0;
}
