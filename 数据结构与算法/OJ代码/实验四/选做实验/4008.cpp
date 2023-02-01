#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
//n2,1 
typedef struct
{
	int vexnum;
	int matrix[100][100];
}AMGraph;
void Create(AMGraph& amg,int n,int m)
{
	amg.vexnum = n;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			amg.matrix[i][j] = 0;
	for (int i = 0; i <= n; i++)
	{
		amg.matrix[i][0] = i;
		amg.matrix[0][i] = i;
	}
	int h, k;
	for (int i = 0; i < m; i++)
	{
		cin >> h >> k;
		amg.matrix[h][k] = 1;
		amg.matrix[k][h] = 1;
	}
	int p1, p2;
	cin >> p1 >> p2;
	amg.matrix[p1][p2] = 1;
	amg.matrix[p2][p1] = 1;
}
void Show(AMGraph amg,int n)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (j != 0)
				cout << ' ';
			cout << amg.matrix[i][j];
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
