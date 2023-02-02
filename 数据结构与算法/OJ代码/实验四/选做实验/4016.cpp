#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

int flag = 0;
typedef struct BNode
{
	char data;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
void Create(BTree& bt, string s, int &i)
{
	if (s[i] == '#')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->data =s[i];
		Create(bt->lchild, s,++i);
		Create(bt->rchild, s,++i);
	}
}
void Traverse(BTree bt)
{
	if (bt)
	{
		if (bt->lchild && bt->rchild)
		{
			if (bt->lchild->data > bt->data || bt->rchild->data < bt->data)
			{
				flag = 1;
				return;
			}
			else
			{
				Traverse(bt->lchild);
				Traverse(bt->rchild);
			}
		}
		else if (bt->lchild && !bt->rchild)
		{
			if (bt->lchild->data > bt->data)
			{
				flag = 1;
				return;
			}
			else Traverse(bt->lchild);
		}
		else if (!bt->lchild && bt->rchild)
		{
			if (bt->rchild->data < bt->data)
			{
				flag = 1;
				return;
			}
			else Traverse(bt->rchild);
		}
	}

}
int main()
{
	string s;
	while (cin >> s && s != "#")
	{
		BTree bt;
		int i = -1;
		Create(bt, s, ++i);
		Traverse(bt);
		if (flag == 0)
			cout << "YES" << endl;
		else cout << "NO" << endl;
		flag = 0;
	}
	return 0;
}

