#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;
int cmp(char a, char b)
{	//字符排列顺序按照ASCII码从小到大的顺序。
	return a < b;
}
void Show(string s)
{
	int cnt = 1;
	char c;
	string temp = "";
	for (int i = 0; i < s.length(); i++)
	{//当前字符为大写字母或数字
		if (isalnum(s[i]) && s[i] < 97)
			temp = temp + s[i];
	}
	c = temp[0];
	if (c == '\0')
	{
		cout << 0 << endl;
		return;
	}
	for (int i = 1; i < temp.length(); i++)
	{
		if (temp[i] == c)
			cnt++;
		else
		{
			printf("%c:%d\n", c, cnt);
			c = temp[i];
			cnt = 1;
		}
	}
	printf("%c:%d\n", c, cnt);//最后一个字符是不会与别的比较的，记得单独输出它
}
int main()
{
	string s;
	while (getline(cin,s)&&s!="0")//getline输入可以带空格，如果不考虑带空格字符串的输入就会WA
	{
		char c[1000];
		s.copy(c, s.length(), 0);//这里s.length()代表复制几个字符，0代表复制的位置，
		*(c + s.length()) = '\0';//注意手动加结束符！！！
		sort(c, c + s.length(), cmp);
		s = c;
		Show(s);
		strcpy(c, "");//vs 2019要写成strcpy_s，但是oj上记得把_s去了
	}
	return 0;
}
