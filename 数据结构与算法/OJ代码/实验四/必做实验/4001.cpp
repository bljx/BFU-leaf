#include <iostream>
using namespace std;

typedef struct {
	char vex[50];//顶点表
	int matrix[50][50];//邻接矩阵
	int vexnum, arcnum;//图的当前点数和边数
}AMGraph;
int path[50], pre[50];
char IndexVex(AMGraph amg, int u) 
{//存在则返回u在顶点表中的下标，否则返回-1
	return amg.vex[u];
}

int GetPos(AMGraph amg, char v)
 {
	for (int i = 0; i < amg.vexnum; i++) 
	{
		if (v == amg.vex[i])//输入的顶点v在amg中找到
			return i;
	}
	return -1;
}
int Create(AMGraph& amg,int vex,int edge)
 {//采用邻接矩阵表示法，创建有向网amg
	char v1, v2;
	int w;

	amg.vexnum = vex;//总顶点数
	amg.arcnum = edge;//总边数
	for (int i = 0; i < amg.vexnum; ++i)
		cin >> amg.vex[i];
	for (int i = 0; i < amg.vexnum; ++i)//初始化邻接矩阵，边的最大权值设置为极大值10000
		for (int j = 0; j < amg.vexnum; ++j)
			amg.matrix[i][j] = 10000;
	int i, j;
	for (int k = 0; k < amg.arcnum; ++k)
	 {//构造邻接矩阵
		cin >> v1 >> v2 >> w;//输入一条边依附的顶点及权值
		i = GetPos(amg, v1);
		j = GetPos(amg, v2);//确定v1和v2在amg中的位置，即顶点数组的下标
		amg.matrix[i][j] = w;//边<v1,v2>的权值置为w
		//amg.matrix[j][i] = amg.matrix[i][j];//置<v1,v2>的对称边<v2,v1>的权值为w
	}//for
	return 1;
}
/*
* 迪杰斯特拉算法的实现
* 假设用带权的邻接矩阵matrix来表示带权有向网amg,amg.matrix[i][j]表示弧<vi,vj>上的权值。
* 若<vi,vj>不存在，则置amg.matrix[i][j]为无穷大，源点v0
* 算法的实现要引入以下辅助的数据结构
* ①一维数组pre[i]:记录从源点v0到终点vi是否已被确定最短路径长度，true表示确定，false表示尚未确定
* ②二维数组pre[i]:记录从源点v0到终点vi的当前最短路径上vi的直接前驱顶点序号。
* 其初值为:如果从v0到vi有弧，则pre[i]为v0;否则为-1
* ③一维数组path[i]:记录从源点v0到终点vi的当前最短路径上vi的当前最短路径长度。其初值为:如果从v0
* 到vi有弧，则path[i]为弧上的权值；否则为正无穷
*/

void Find(AMGraph amg, char V)
 {//用Dijkstra算法求有向网amg的v0顶点到其余顶点的最短路径
	int nextvex, min;
	int visit[50];
	int pos = GetPos(amg, V);
	for (int i = 0; i < amg.vexnum; i++)
	{
		visit[i] = false;//visit初始为空集
		path[i] = amg.matrix[pos][i];//将pos到各个终点的最短路径长度初始化为弧上的权值
		if (path[i] < 10000) 
			pre[i] = pos;//如果pos和i之间有弧，则将i前驱置为pos
		else
			pre[i] = -1;//如果pos和i之间无弧，则将i前驱置为-1
	}
	visit[pos] = true;//将pos加入visit
	path[pos] = 0;//源点到源点的距离为0
	/*————————初始化结束，开始主循环，每次求得pos到某个顶点v的最短路径，将v加到visit集————————*/
	for (int i = 1; i < amg.vexnum; i++) 
	{//对其余amg.vexnum-1个顶点，依次进行计算
		min = 10000;
		for (int j = 0; j < amg.vexnum; ++j)
		 {
			if (!visit[j] && path[j] < min) 
			{
				nextvex = j;
			    min = path[j];//选择一条当前的最短路径，终点为nextvex 
			}
		}
		visit[nextvex] = true;//将nextvex加入visit
		for (int j = 0; j < amg.vexnum; j++) 
		{//更新从pos出发到集合V-visit上所有顶点的最短路径长度
			if (!visit[j] && (path[nextvex] + amg.matrix[nextvex][j] < path[j]))
			{
				path[j] = path[nextvex] + amg.matrix[nextvex][j];//更新path[j]
				pre[j] = nextvex;//更改j的前驱为nextvex
			}
		}
	}
}

void Show(AMGraph amg, int v) 
{
	if (pre[v] == -1)
		return;
	else 
	{
		Show(amg, pre[v]);
		cout << IndexVex(amg, pre[v]) << " ";
	}
}

int main() {
	char city1, city2;//城市名字，起点、终点
	int a, b;//n个城市，m条路径
	while (cin >> a >> b && a && b)
	{
		AMGraph amg;
		Create(amg, a, b);
		cin >> city1>>city2;
		Find(amg, city1);
		cout << path[GetPos(amg, city2)] << endl;
		Show(amg, GetPos(amg, city2));
		cout << city2 << endl;
	}
	return 0;
}

