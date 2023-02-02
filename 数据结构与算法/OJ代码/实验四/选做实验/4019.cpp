#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

int cnt;
typedef struct BNode
{
	int bal;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
void Create(BTree& bt, string s, int i)
{
	if (s[i] == '#')
		bt = NULL;
	else
	{
		bt = new BNode;
		bt->bal = s[i] - '0';
		Create(bt->lchild, s, ++i);
		Create(bt->rchild, s, ++i);
	}
}
void Traverse(BTree bt)
{
	if (bt)
	{
		cnt++;
		if (bt->bal == 1)
			Traverse(bt->lchild);
		else
			Traverse(bt->rchild);
	}
}
int main()
{
	string s;
	while (cin >> s && s != "#")
	{
		int i = -1;
		BTree bt = NULL;
		Create(bt, s, ++i);
		Traverse(bt);
		cout << cnt << endl;
		cnt = 0;
	}
	return 0;
}
