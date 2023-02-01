#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
float maxprice = 0.00;
int maxarr[100];
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
	for (int i = 0; i <n; i++)
	{
		cin >> l.elem[i].id >> l.elem[i].name >> l.elem[i].price;
		maxarr[(int)l.elem[i].price]++;
		if (maxprice < l.elem[i].price)
			maxprice = l.elem[i].price;
		l.length++;
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
void Find(Sqlist l)
{
	cout << maxarr[(int)maxprice] << endl;
	for (int i = 0; i < l.length; i++)
	{
		if (l.elem[i].price == maxprice)
			printf("%s %s %.2f\n", l.elem[i].id.c_str(), l.elem[i].name.c_str(), l.elem[i].price);
		else return;
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
	Sort(l);
	Find(l);
}

