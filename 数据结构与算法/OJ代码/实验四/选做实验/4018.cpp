#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

typedef struct BNode
{
	int data, count;
	struct   BNode* lchild, * rchild;
}*BTree, BNode;
int arr[100];
void Create(BTree& bt, int x)
{
	if (!bt)
	{
		bt = new BNode;
		bt->data = x;
		arr[x] = 1;
		bt->count = 0;
		bt->lchild = NULL;
		bt->rchild = NULL;
	}
	else
	{
		if (x < bt->data)
			Create(bt->lchild, x);
		else
			Create(bt->rchild, x);
	}
}
void Traverse(BTree &bt,int x)
{
	while (bt)//是不是递归和非递归之间转化的精髓就是是用if还是用while？
	{
		if (arr[x] == 0)
		{
			if (bt->data < x)
			{
				while (bt->rchild != NULL && bt->rchild->data < x)
					bt = bt->rchild;

			}
			else if (bt->data < x)
			{
				while (bt->lchild != NULL && bt->lchild->data > x)
					bt = bt->lchild;
			}
			BTree temp = new BNode;
			temp->data = x;
			temp->count = 0;
			temp->rchild = NULL;
			temp->lchild = NULL;
			bt->lchild = temp;
			arr[x] = 1;
		}
		else
		{
			if (bt->data < x)
				bt = bt->rchild;
			else if (bt->data > x)
				bt = bt->lchild;
			else 
			{
				bt->count=1;
				return;
			}
		}
	}
}
void PrintData(BTree bt,int& n)
{
	if(bt)
	{
		cout << bt->data;
		n--;
		if (n)
			cout << ' ';
		PrintData(bt->lchild,n);
		PrintData(bt->rchild,n);
	}
}
void PrintCount(BTree bt,int& n)
{
	if (bt)
	{
		cout << bt->count;
		n--;
		if (n)
			cout << ' ';
		PrintCount(bt->lchild,n);
		PrintCount(bt->rchild,n);
	}
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		BTree bt=NULL,ass;
		int x;
		for (int i = 0; i < n; i++)
		{
			cin >> x;
			Create(bt, x);
		}	
		cin >> x;
		if (arr[x] == 0)
			n += 1;
		ass = bt;
		Traverse(bt, x);
		int n1 = n, n2 = n;
		PrintData(ass,n1);
		cout << endl;
		PrintCount(ass,n2);
		cout << endl;
		for (int i = 0; i < 100; i++)
			arr[i] = 0;
	}
	return 0;
}

