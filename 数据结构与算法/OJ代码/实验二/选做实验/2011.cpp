#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
//n,1
int Ans(int m,int n)
{
	if (m == 0)
		return n + 1;
	int ack[10][50];
	for (int i = 0; i < 100; i++)
		ack[0][i] = i + 1;
	for (int i = 1; i <= m; i++)
	{
		ack[i][0] = ack[i - 1][1];
		for (int j = 1; j < 100; j++)
			ack[i][j] = ack[i - 1][ack[i][j - 1]];
	}
	return ack[m][n];
}
int main()
{
	int m, n;
	while (cin >> m >> n && m != 0 && n != 0)
		cout << Ans(m, n) << endl;
	return 0;
}
