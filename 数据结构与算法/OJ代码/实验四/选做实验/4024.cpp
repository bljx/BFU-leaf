#include<bits/stdc++.h>
using namespace std;

int red=0, blue=0, white=0;
void Count(char c)
{
	if (c == 'R')
		red++;
	else if (c == 'W')
		white++;
	else
		blue++;
}
void Show()
{
	for (int i = 0; i < red-1; i++)
		cout << "R ";
	if(red&&blue&&white)
		cout << "R ";
	for (int i = 0; i < white - 1; i++)
		cout << "W ";
	if(blue&&white)
		cout << "W ";
	for (int i = 0; i < blue - 1; i++)
		cout << "B ";
	cout << "B" << endl;
}
int main()
{
	int n;
	while (cin >> n && n != 0)
	{
		for (int i = 0; i < n; i++)
		{
			char c;
			cin >> c;
			Count(c);
		}
		Show();
		red = 0;
		blue = 0;
		white = 0;
	}
	return 0;
}
