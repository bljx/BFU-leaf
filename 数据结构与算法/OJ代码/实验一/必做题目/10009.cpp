#include<string>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
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
		cin >> l.elem[i].id >> l.elem[i].name >> l.elem[i].price;
		l.length++;
	}
}
void FindPos(Sqlist l, int pos)
{
	if (pos <= 0|| pos >= l.length)
		cout << "Sorry£¬the book on the best position doesn't exist!" << endl;
	else
		printf("%s %s %.2f\n", l.elem[pos].id.c_str(), l.elem[pos].name.c_str(), l.elem[pos].price);
}
int main()
{
	Sqlist l;
	Init(l);
	int t;
	cin >> t;
	Insert(l,t);
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int p;
		cin >> p;
		FindPos(l, p);
	}
	return 0;
}

