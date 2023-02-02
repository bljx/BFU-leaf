#include<string>
#include<iostream>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
set<string> s;
class Book
{
public:
	string id, name;
	float price;
};
class Sqlist
{
public:
	int length;
	Book* elem;
};
void Init(Sqlist& l)
{
	l.elem = new Book[1000];
	if (!l.elem)
		exit(1);
	l.length = 0;
}
void Insert(Sqlist& l,int n)
{
	for (int i = 1; i <= n; i++)
	{
 
		Book t;
		cin >> t.id >> t.name >> t.price;
		pair<set<string>::iterator, bool> ret = s.insert(t.id);
		if (ret.second)
		{
			l.elem[l.length+1] = t;
		    s.insert(t.id);
			l.length++;
		}
	}
}
void Print(Sqlist l)
{
	cout << l.length << endl;
	for (int i = 1; i <= l.length; i++)
		printf("%s %s %.2f\n", l.elem[i].id.c_str(), l.elem[i].name.c_str(), l.elem[i].price);
}
int main()
{
	Sqlist l;
	Init(l);
	int t;
	cin >> t;
	Insert(l,t);
	Print(l);
	return 0;
}

