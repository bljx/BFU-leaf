#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int BFind(string v, string h)
{
	int i = 0, j = 0, flag = 0;
	while (i < h.size() && j < v.size())
	{
		if (v[j] == h[i])
		{
			i++;
			j++;
			flag++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
			flag = 0;
		}
	}
	return flag;
}
int main()
{
	string virus, human;
	while (cin >> virus >> human && virus != "0" && human != "0")
	{
		int vlen = virus.length(), ans = 0;
		virus += virus;//把这个字符串扩充为原来的两倍，再依次取出长度比对就行了……先用BF试一试
		for (int i = 0; i < vlen; i++)
		{
			string v = virus.substr(i, vlen);
			ans = BFind(v, human);
			if (ans == v.length())
			{
				cout << "YES" << endl;
				break;
			}
		}
		if (ans == 0)
			cout << "NO" << endl;
	}
	return 0;
}
