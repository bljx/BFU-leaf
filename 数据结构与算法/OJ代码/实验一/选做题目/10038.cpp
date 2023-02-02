#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
void InitList(LinkList& L, int m)
{
    L = new LNode;
    L->data = 1;
    L->next = NULL;
    LinkList p = L;
    for (int i = 2; i <= m; i++)
    {
        LinkList q = new LNode;
        q->data = i;
        q->next = NULL;
        p->next = q;
        p = q;
    }
    p->next = L;
    L = p;
}
void MonkeyKing(LinkList& L, int n)
{
    while (L->next != L)
    {
        for (int i = 1; i < n; i++)
            L = L->next;
        LinkList s = L->next;
        cout << s->data << " ";
        L->next = s->next;
        delete(s);
    }
    cout << L->data << endl;	
}
int main()
{
    int m, n;
    while (cin >> m >> n && m != 0 && n != 0)
    {
        LinkList L;
        InitList(L, m);
        MonkeyKing(L, n);
    }
    return 0;
}
