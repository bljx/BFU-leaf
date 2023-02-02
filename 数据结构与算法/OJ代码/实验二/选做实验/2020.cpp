#include<iostream>
#include<string>
//2020£¬ANAN  www 
//1 £¬1 
using namespace std;
void Insert(char* main, char* sub, int pos)
{
	string m = main, s = sub;
	for (int i = 0; i < pos-1; i++)
		cout << m[i];
	for (int i = 0; i < s.length(); i++)
		cout << s[i];
	for (int i = pos-1; i < m.length(); i++)
		cout << m[i];
	cout << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		char main[50] = {}, sub[50] = {};
		cin >> main >> sub;
		Insert(main, sub, n);
	}
	return 0;
}
