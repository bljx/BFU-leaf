#include <iostream>
using namespace std;
//n£¬n 
typedef struct BNode
{
	char data;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
int zero, one, two;
void Create(BTree& bt )
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
void Create(BTree& bt,char c)
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
		if (bt->lchild && bt->rchild)
			two++;
		else if (bt->lchild || bt->rchild)
			one++;
		else
			zero++;
		Traverse(bt->lchild);
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
		cout << zero << " " << one << " " << two << endl;
		zero = 0;
		one = 0;
		two = 0;
	}
	return 0;
}
