#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
typedef struct BNode
{
	char data;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
void Create(BTree& bt)
{
	char c;
	cin >> c;
	if (c == '0')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->data = c;
		Create(bt->lchild);
		Create(bt->rchild);
	}
}
void Create(BTree& bt, char c)
{
	if (c == '0')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->data = c;
		Create(bt->lchild);
		Create(bt->rchild);
	}
}
void Traverse(BTree bt)
{
	if (bt == NULL)
		return;
	else
	{
		cout << bt->data;
		Traverse(bt->lchild);
		cout << bt->data;
		Traverse(bt->rchild);
	}
}
int main()
{
	while (1)
	{
		char c;
		cin >> c;
		if (c == '0')
			break;
		BTree b;
		Create(b, c);
		Traverse(b);
		cout << endl;
	}
	return 0;
}
