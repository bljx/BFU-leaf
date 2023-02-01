#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;
int flag, out;
int map[100][3],mark[100];
//map表示的是地图，mark标记当前位置是不是走过了
void DFS(int n)//n是现在的行数
{
	if (n == out)
	{
		flag = 1;//找到出口，可以退出了，因为这个题考的不是最短路径而是能不能走出去
		return;
	}
	//else，还没找到出口or没有出口
	for (int i = 0; i < 3; i++)//对每一行的三个数值都调用DFS
	{
		//map当前的路口不是0，并且这个位置还没有被mark
		if ( map[n][i]  && mark[map[n][i]]==0)
		{
			mark[map[n][i]] = 1;//先标记走过了
			DFS(map[n][i]);//从当前位置继续找
			mark[map[n][i]] = 0;
		}
	}
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		flag = 0;
		//n个路口是从1开始编号的……所以如果你从0开始计数就会WA……
		for (int i = 1; i <= n; i++)
			mark[i] = 0;
		//上面三个语句是为了每次初始化，第一次确实不用
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < 3; j++)
				cin >> map[i][j];
		cin >> out;
		mark[1] = 1;//首先初始位置肯定是「走过的」
		DFS(1);
		if (flag == 1)
			cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
