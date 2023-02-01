#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;
typedef struct BNode
{
	char data;
	struct BNode* lchild, * rchild;
}*BTree, BNode;
vector<char> ans(100);
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
void DFSTraverse(BTree bt,int x)
{
	if (bt)
	{
		ans[x] = bt->data;//如果当前节点存在，那么就从它这里走，它就算路径，在第几步走到了它（下标）存储它
		if (!bt->lchild && !bt->rchild)//是叶子节点，那么可以输出遍历后的结果了
		{
			for (int i = x; i >= 1; i--)//由于是从叶子到根，所以要倒序遍历，x一开始传的是1，所以到1截止
				cout << ans[i];
			cout << endl;
		}
        /*
        重点：
        	 我什么时候要再次调用算法？
        	 回答：想一想，DFS叫做“深度优先遍历”算法，用你的语文知识分析一下：“深度优先”是状语，是对算法的应用范围加以限制的，算法的主语是“遍历”，所以DFS是“用来遍历的算法”，那么要访问其他节点的时候就会自然而然地用到DFS了。反映到题目里就是：如果不是叶子节点，还需要继续「遍历」的时候，就会调用它。
        	 
        	 调用算法的时候每个参数的含义都是什么？该如何处理算法中的参数才是正确的？
        	 回答：首先需要把“地图”传进去吧，这个无需多言；第二个参数是我们需要仔细分析的。首先从这个题目上来看，同一结点的两个叶子节点在ans中会主动覆盖（因为路径长度一样，所以下标一样，所以在遍历右叶子节点的时候，会自动覆盖上一次存入的左叶子节点的信息），所以对叶子节点来说，不存在走到“else”的情况，不会用到DFS，忽略；再看普通节点：它们是有顺序的，每一次调用都说明又走了一步，因此它们之间不允许覆盖，所以要让ans[x]按顺序存储，就要在每次调用DFS的时候保证x每次都加1，以便让新节点存到新空间里，所以答案就浮出水面了——第二个参数写x+1.
        */
		else
		{
			DFSTraverse(bt->lchild,x+1);
			DFSTraverse(bt->rchild,x+1);
		}
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
        /////////////////////
		int x = 0;//x就代表了当前已经走过结点的个数，又因为x是递增的，且每次调用都只加1，所以就相当于变相的记录了每一步都从谁那里取道
		DFSTraverse(b, x+1);//所以其实一开始是把1传进去的
        /////////////////////
    }
	return 0;
}
