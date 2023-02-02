#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
//n2£¬1 
typedef struct
{
	int nowvex;
	int matrix[100][100];
}AMGraph;
void Create(AMGraph& amg,int n,int m)
{
	amg.nowvex = n;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			amg.matrix[i][j] = 0;
	for (int i = 0; i <= n; i++)
	{
		amg.matrix[0][i] = i;
		amg.matrix[i][0] = i;
	}
	int h, k;
	for (int i = 0; i < m; i++)
	{
		cin >> h >> k;
		amg.matrix[h][k] = 1;
		amg.matrix[k][h] = 1;
	}
}
void Show(AMGraph amg,int n)
{
	int p;
	cin >> p;
	for (int i = 0; i <= n; i++)
	{
		if (i == p)
			continue;
		for (int j = 0; j <= n; j++)
		{
			if (j == p)
				continue;
			else
			{
				if (j != 0)
					cout << ' ';
				cout << amg.matrix[i][j];
			}
		}
		cout << endl;
	}
}
int main()
{
	int m, n;
	while (cin >> n >> m && m != 0 && n != 0)
	{
		AMGraph amg;
		Create(amg, n, m);
		Show(amg, n);
	}
	return 0;
}

