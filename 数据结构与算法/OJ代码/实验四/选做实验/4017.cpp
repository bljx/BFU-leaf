#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;
 
vector<int> v;
typedef struct BNode
{
	int data;
	struct   BNode* lchild, * rchild;
}*BTree, BNode;
void Create(BTree& bt,int x)
{
	if (!bt)
	{
		bt = new BNode;
		bt->data = x;
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
void Traverse(BTree bt,int x)
{
	if (bt)
	{
        if (bt->data >= x)
			v.push_back(bt->data);
		Traverse(bt->lchild, x);
		Traverse(bt->rchild, x);
	}
}
void Print()
{
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size()-1; i++)
		cout << v[i]<<' ';
	cout <<v[v.size()-1]<< endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		BTree bt=NULL;
		int x;
		for (int i = 0; i < n; i++)
		{
			cin >> x;
			Create(bt, x);
		}	
		cin >> x;
		Traverse(bt,x);
		Print();
		v.clear();
	}
	return 0;
}
