#include <iostream>
using namespace std;
//n,n 
typedef struct BNode
{
	char data;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
void XCreate(BTree& bt)//这个函数是因为要用到第一个字符来插入，所以有两个参数 
{
	char c;
	cin >> c;
	if (c == '0')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->data = c;
		XCreate(bt->rchild);
		XCreate(bt->lchild);
	}
}
void XCreate(BTree& bt,char c)//重载 
{
	if (c == '0')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->data = c;
		XCreate(bt->rchild);
		XCreate(bt->lchild);
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
		XCreate(b,c);
		Traverse(b);
		cout << endl;
	}
	return 0;
}
