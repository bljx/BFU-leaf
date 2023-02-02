#include <iostream>
using namespace std;
//n£¬n 
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
	if(bt)
	{
		cout << bt->data;
		Traverse(bt->lchild);
		Traverse(bt->rchild);
	}
}
void LTraverse(BTree bt)
{
	if (bt)
	{
		LTraverse(bt->lchild);
		cout << bt->data;
		LTraverse(bt->rchild);
	}
}
void RTraverse(BTree bt)
{
	if (bt)
	{
		RTraverse(bt->lchild);
		RTraverse(bt->rchild);
		cout << bt->data;
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
		LTraverse(b);
		cout << endl;
		RTraverse(b);
		cout << endl;
	}
	return 0;
}
