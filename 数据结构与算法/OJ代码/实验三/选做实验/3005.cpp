#include <iostream>
#include <vector>
using namespace std;
typedef struct BNode
{
	char data;
	int level;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
int lv = 1;
int Floor[200];
void Create(BTree& bt, string s, int& i)//ÒýÓÃi£¡£¡£¡
{
	if (s[i] == '0')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->data = s[i];
		bt->level = lv;
		Create(bt->lchild, s, ++i);
		Create(bt->rchild, s, ++i);
	}
}
void Setlevel(BTree bt)
{
	if (bt)
	{
		if (bt->lchild || bt->rchild)
		{
			lv = lv >= bt->level ? lv : bt->level;
			++lv;
			if (bt->lchild && bt->rchild)
			{
				bt->lchild->level = lv;
				bt->rchild->level = lv;
			}
			else if (bt->lchild && !bt->rchild)
				bt->lchild->level = lv;
			else
				bt->rchild->level = lv;
			Setlevel(bt->lchild);
			Setlevel(bt->rchild);
		}
		else
			lv = bt->level - 1;
	}
}
void Traverse(BTree bt)
{
	if (bt)
	{
		Floor[bt->level]++;
		Traverse(bt->lchild);
		Traverse(bt->rchild);
	}
}
int main()
{
	string s;
	while (cin >> s && s != "0")
	{
		int i = -1;
		BTree b;
		Create(b, s, ++i);
		b->level = 1;
		Setlevel(b);
		Traverse(b);

		int maxi = Floor[1];
		for (int i = 2; i < 200; i++)
		{
			if (Floor[i] > maxi)
				maxi = Floor[i];
			if (Floor[i] == 0)
				break;
		}
		cout << maxi << endl;

		lv = 1;
		for (int i = 1; i < 200; i++)
		{
			if (Floor[i] == 0)
				break;
			Floor[i] = 0;
		}
	}
	return 0;
}

