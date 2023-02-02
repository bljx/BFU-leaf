#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include<set>
#include<algorithm>
using namespace std;
typedef struct Stack
{
	char s;
	struct Stack* next;
}*linkstack, SNode;
void Init(linkstack& s)
{
	s = NULL;
}
void Insert(linkstack& l,char x)
{
	linkstack p = new SNode;
	p->s = x;
	p->next = l;
	l = p;
}
bool Empty(linkstack s)
{
	if (s == NULL)
		return true;
	return false;
}
char Pop(linkstack& l)
{
	if (l == NULL)
		return 0;
	linkstack p;
	char e = l->s; 
	p = l;
	l = l->next;
	delete p;
	return e;
}
void Compare(linkstack s1, linkstack s2)
{
	while (!Empty(s1))
	{
		if (Pop(s1) != Pop(s2))
		{
			cout << "NO" << endl;
			return;
		}
	}
	cout << "YES" << endl;
}
int main()
{
	string s;
	cin >> s;
	while (s != "0")
	{
		linkstack s1, s2;
		Init(s1);
		Init(s2);
		for (int i = 0; i < s.length(); i++)
			Insert(s1,s[i]);
		for (int i = s.length() - 1; i >= 0; i--) 
			Insert(s2, s[i]);
		Compare(s1, s2);
		cin >> s;
	}
	return 0;
}
