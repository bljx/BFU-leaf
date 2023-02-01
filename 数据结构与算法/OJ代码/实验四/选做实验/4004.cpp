	#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#define MaxLen 30000
#define MaxVex 100
using namespace std;
//n2£¬1 
typedef struct
{
	int arcs[MaxVex][MaxVex];
	int nowvex, nowarcs;
}AMGraph;
void Create(AMGraph& amg, int vexnum, int arcnum)
{
	amg.nowvex = vexnum;
	amg.nowarcs = arcnum;
	if (amg.nowvex > MaxVex)
		exit(-1);
	for (int i = 0; i <= amg.nowvex; i++)
	{
		amg.arcs[i][0] = i;
		amg.arcs[0][i] = i;
	}
	//for (int i = 0; i <= amg.nowvex; i++)
	//{
	//	for (int j = 0; j <= amg.nowvex; j++)
	//		cout << amg.arcs[i][j] << ' ';
	//	cout << endl;
	//}
	for (int i = 1; i < MaxVex; i++)
		for (int j = 1; j < MaxVex; j++)
			amg.arcs[i][j] = 0;
	int h, k;
	for (int i = 1; i <= amg.nowarcs; i++)
	{
		cin >> h >> k;
		amg.arcs[h][k] = 1;
		amg.arcs[k][h] = 1;
	}
}
void Insert(AMGraph& amg)
{
	if (amg.nowvex + 1 > MaxVex)
		exit(-1);
	int p;
	cin >> p;
	amg.nowvex++;
	amg.arcs[0][amg.nowvex] = p;
	amg.arcs[amg.nowvex][0] = p;
	for (int i = 1; i <= amg.nowvex; i++)//4
	{
		amg.arcs[i][amg.nowvex] = 0;
		amg.arcs[amg.nowvex][i] = 0;
	}
}
void Show(AMGraph amg)
{
	for (int i = 0; i <= amg.nowvex; i++)
	{
		for (int j = 0; j <= amg.nowvex; j++)
		{
			if (j != 0)
				cout << ' ';
			cout << amg.arcs[i][j];	
		}
		cout  << endl;
	}
}
int main()
{
	int n, m;
	while (cin >> n >> m && m != 0 && n != 0)
	{
		AMGraph amg;
		Create(amg, n, m);
		Insert(amg);
		Show(amg);
	}
	return 0;
}
