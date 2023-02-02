#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<map>
using namespace std;

typedef struct
{
	int matrix[50][50];
}AMGraph;
int path[50];
int visit[50];
void Init(AMGraph &amg,int n,int m)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			amg.matrix[i][j] = 100;
	int h, k, len;
	for (int i = 0; i < m; i++)
	{
		cin >> h >> k >> len;
		amg.matrix[h][k] = len;
		amg.matrix[k][h] = len;
	}
}
void DFind(AMGraph amg,int n)
{
	int p;
	cin >> p;
	for (int i = 1; i <= n; i++)
	{
		path[i] = amg.matrix[p][i];
		visit[i] = 0;
	}
	path[p] = 0;
	visit[p] = 1;
	int nextvex = 0,min;
	for (int j = 1; j < n; j++)//n个节点，比n-1次！
	{
		min = 100;
		//第一步，找nextvex，从
		for (int i = 1; i <= n; i++)
		{//自己写漏了visit的改变。。只能在没访问过的节点里找呀！！
			if (!visit[i]&&amg.matrix[p][i] < min)
			{
				min = amg.matrix[p][i];
				nextvex = i;
			}
		}
		visit[nextvex] = 1;
		for (int i = 1; i <= n; i++)//下面这个if想那个三角形的路线图
			if (!visit[i]&&path[i]>path[nextvex]+amg.matrix[nextvex][i])//这句也忘了，它自己肯定不用更新了啊，是以它为节点更新别的点的距离
			//反典：path[i] = (path[i] > amg.matrix[p][i] + min) ? (amg.matrix[p][i] + min) : path[i];
			{
				path[i] = path[nextvex] + amg.matrix[nextvex][i];
			}
	}
}
void Show(AMGraph amg,int n)
{
	int point=1, len=0;
	for (int i = 1; i <= n; i++)
	{	//最长的啊。。咋这还能错呢
		if (path[i] > len)
		{
			point = i;
			len = path[i];
		}
	}
	cout << point << endl << len << endl;
}
int main()
{
	int n, m;
	while (cin >> n >> m && n != 0 && m != 0)
	{
		AMGraph amg;
		Init(amg, n, m);
		DFind(amg, n);
		Show(amg, n);
	}
}
