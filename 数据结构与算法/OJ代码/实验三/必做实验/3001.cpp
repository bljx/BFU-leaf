#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
using namespace std;
/*BGM： 《没有共产党就没有新中国》
		《沂蒙山小调》
		《洪湖水浪打浪》
		《拔根芦柴花》
		《送肥忙》 
*/
typedef struct HNode
{
	char data;//数据 
	int parent, weight, lchild, rchild;//双亲，权值，左右孩子 
	string code;//每个节点自己的哈夫曼代码 
}*HTree, HNode;
void DeCode(HTree ht, string s, int m)//解码 
{
	int i = m, j = 0;
	while (s[j])
	{
		if (s[j] == '0')
			i = ht[i].lchild;
		else
			i = ht[i].rchild;
		if (ht[i].lchild == 0 && ht[i].rchild == 0)//是叶子节点
		{
			cout << ht[i].data;
			i = m;//回到根节点
		}
		j++;
	}
}
void Cout(map<char, int> m, int size, HTree ht, string s)
{
	//打印字符和频率
	for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		if (it != m.begin())
			cout << " ";
		printf("%c:%d", it->first, it->second);
	}
	cout << endl;
	//打印表格
	for (int i = 1; i <= size * 2 - 1; i++)
		printf("%d %d %d %d %d\n", i, ht[i].weight, ht[i].parent, ht[i].lchild, ht[i].rchild);
	//打印字符及其对应的Huffman Code
	for (int i = 1; i <= size; i++)
	{
		if (i != 1)
			cout << " ";
		printf("%c:%s", ht[i].data, ht[i].code.c_str());
	}
	cout << endl;

	map<char, int>::iterator it = m.begin();
	string decode;
	for (int i = 0; i < s.length(); i++)//i控制输出次数
	{
		for (int k = 1; k <= size; k++, it++)//匹配ht里的data和当前字符
		{
			if (ht[k].data == s[i])//找到了
			{
				cout << ht[k].code;
				decode += ht[k].code;
				break;
			}
		}
		it = m.begin();
	}
	cout << endl;
	DeCode(ht, decode, size * 2 - 1);//解码
	cout << endl;
}
pair<pair<int, int>, pair<int, int>> FindParent(map<int, int>& ass, HTree ht, int size,int nowsize)//小蝌蚪找妈妈(大雾）
{
	int min1 = 30000, min2 = 30000;//记录当前的两个最小权值 
	int p1 = 0, p2 = 0;
	int i = 0, j = 0;//记录当前节点的两个孩子 
	for (map<int, int>::iterator it = ass.begin(); it != ass.end(); it++)
	{
		if (it->first < min1 && it->second == 1)
		{
			min1 = it->first;
			it->second = 0;
		}
	}
	for (map<int, int>::iterator it = ass.begin(); it != ass.end(); it++)
	{
		if (it->first < min2 && it->first != min1 && it->second == 1)
		{
			min2 = it->first;
			it->second = 0;
		}
	}
	if (min2 == 30000)//测试用例2
		min2 = min1;
	for (int k = 1; k < size; k++)
	{
		if (ht[k].weight == min1)
			i = k;
		if (ht[k].weight == min2)
			j = k;
		if (i != 0 && j != 0)
			break;
	}
	if (min1 == min2)//测试用例2
	{
		int flag = 0;
		for (int k = 1; k <= nowsize; k++)
		{
			if (min1 == ht[k].weight)
				flag++;
			if (flag == 2)
			{
				j = k; 
				break;
			}
		}
 	}
	pair<int, int > weight = make_pair(min1, min2);
	pair<int, int > parent = make_pair(i, j);
	pair< pair<int, int>, pair<int, int>>ans = make_pair(weight, parent);
	return ans;
}
void Create(HTree& ht, int size, map<char, int> mp, map<int, int>ass)//构造哈夫曼树
{
	if (size <= 1)
		return;
	else
	{
		int m = size * 2 - 1;//最多有这么多个节点
		int patch = m + 1;//如果不这么写，在下面的[]里写m+1的话，oj会报错compile error 
		ht = new HNode[patch];//0号下标不用，HT[m]表示根结点
		map<char, int>::iterator it = mp.begin();
		for (int i = 1; i <= size; i++, it++)//初始化前面几个有数值的已知节点
		{
			ht[i].lchild = 0;
			ht[i].rchild = 0;
			ht[i].parent = 0;
			ht[i].data = it->first;
			ht[i].weight = it->second;
			ass[it->second] = 1;
		}
		//补齐后面几个节点的weight,lch,rch
		for (int i = size + 1; i <= m; i++)
		{
			pair<pair<int, int>, pair<int, int>>ans = FindParent(ass, ht, m,i);
			ht[i].weight = ans.first.first + ans.first.second;
			ht[i].lchild = ans.second.first;
			ht[i].rchild = ans.second.second;
			ht[ans.second.first].parent = i;
			ht[ans.second.second].parent = i;
			ass[ht[i].weight] = 1;
		}
		ht[m].parent = 0;
	}
}
void SetCode(HTree ht, int size)
{
	for (int i = 1; i <= size; i++)
	{
		int fammem = ht[i].parent;
		while (fammem != 0)
		{
			if (ht[fammem].lchild == i)
				ht[i].code = '0' + ht[i].code;
			else
				ht[i].code = '1' + ht[i].code;
			fammem = ht[fammem].parent;
		}
	}
}
int cmp(char a, char b)
{return a < b;}
void SetMap(map<char, int>& m, string s)
{
	for (int i = 0; i < s.length(); i++)
		m[s[i]]++;
}
int main()
{
	char temp[100];
	while (cin >> temp && temp[0] != '0')
	{
		HTree ans;//胜利在望！
		string s = temp;//为了获取长度
		string cd = temp;//为了记录下原式字符串
		sort(temp, temp + s.length(), cmp);//ASCII排序
		s = temp;//现在再次赋值，是排好序的了
		map<char, int>m;//记录字母种类以及出现次数
		map<int, int>ass;//辅助，为了让min2和min1不一样
		SetMap(m, s);	//存每个字符以及他们的频率到map中，记得参数写引用！！！
		Create(ans, m.size(), m, ass);//创建二叉树
		SetCode(ans, m.size());//为每个节点创建Huffman Code
		Cout(m, m.size(), ans, cd);//输出啦！
	}
	return 0;
}
