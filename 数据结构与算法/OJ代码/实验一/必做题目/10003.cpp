#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
float avg = 0.00;
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
	for (int i = n-1; i >=0; i--)
	{
		cin >> l.elem[i].id >> l.elem[i].name >> l.elem[i].price;
		avg += l.elem[i].price;
		l.length++;
		if (l.elem[i].id == "0" && l.elem[i].name == "0" && l.elem[i].price == 0)
		{
			l.length--;
			avg /= l.length;
			return;
		}
	}
}
void Print(Sqlist l)
{
	for (int i = 0; i <l.length; i++)
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
}

