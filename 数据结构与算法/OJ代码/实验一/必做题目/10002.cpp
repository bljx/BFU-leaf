#include<string>
#include<iostream>
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
void Insert(Sqlist& l)
{
	for (int i = 0; i < 1000; i++)
	{
		cin >> l.elem[i].id >> l.elem[i].name >> l.elem[i].price;
		l.length++;
		if (l.elem[i].id == "0" && l.elem[i].name == "0" && l.elem[i].price == 0)
		{
			l.length--;
			return;
		}
	}
}
void Sort(Sqlist& l)
{
	for (int i = 0; i < l.length - 1; i++)
	{
		for (int j = 0; j < l.length - i - 1; j++) 
		{
			if (l.elem[j].price < l.elem[j + 1].price)
			{
				Book book= l.elem[j];
				l.elem[j] = l.elem[j + 1];
				l.elem[j + 1] = book;
			}
		}
	}
}
void Print(Sqlist l)
{
	//cout << l.length << endl;
	for (int i = 0; i < l.length; i++)
		printf("%s %s %.2f\n", l.elem[i].id.c_str(), l.elem[i].name.c_str(), l.elem[i].price);
}
int main()
{
	Sqlist l;
	Init(l);
	Insert(l);
	Sort(l);
	Print(l);
}

