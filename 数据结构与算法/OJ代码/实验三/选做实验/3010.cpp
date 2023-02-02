#include <iostream>
using namespace std;
typedef struct BNode
{
	char data;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
int max1 = 0, maxi = 0;
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
	if (bt)
	{
		max1++;
		Traverse(bt->lchild);
		Traverse(bt->rchild);
		maxi = max1 > maxi ? max1 : maxi;
		max1--;
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
		cout << maxi << endl;
		maxi = 0;
		max1 = 0;
	}
	return 0;
}
