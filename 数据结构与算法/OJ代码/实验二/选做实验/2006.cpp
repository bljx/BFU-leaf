#include<iostream>
using namespace std;
typedef struct SNode
{
	char data;
	struct SNode* next;
}SNode, * StackList;
int main()
{
	string s;
	while (cin >> s && s!= "0")
	{
		StackList S = NULL, p, q;
		int flag = 1;
		for (int i = 0;i<s.length() ; i++)
		{
			if (s[i] == '\0')
				break;
			if (s[i] == 'I')
			{
				p = new SNode;
				p->next = S;
				S = p;
			}
			if (s[i] == 'O')
			{
				if (S == NULL)
				{
					flag = 0;
					break;
				}
				else
				{
					q = S;
					S = S->next;
					delete q;
				}
			}
		}
		if (flag == 1 && S == NULL)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;
	}
	return 0;
}

