#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}*linklist, LNode;
void Insert(linklist& l, int n)
{
    l = new LNode;
    l->next = NULL;
    linklist rear = l;
    for (int i = 0; i < n; i++)
    {
        linklist p = new LNode;
        cin >> p->data;
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
}
int Num(linklist l)
{return l->next == NULL ? 1 : Num(l->next)+1;}
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        linklist l;
        Insert(l, n);
        cout<<Num(l->next)<<endl;
    }
    return 0;
}
