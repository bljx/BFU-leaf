#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
char Reverse(char a,int now,int n)
{
	if (now == n)
		return a;
	else
		return Reverse('s', now + 1, n);
}
int main()//n,1
{
	string s = "";
	while (cin >> s && s != "0")
	{
		string temp = "";
		for (int i = 0; i < s.length(); i++)
			temp = Reverse(s[i], i, s.length()) + temp;
		cout << temp << endl;
	}
	return 0;
}
