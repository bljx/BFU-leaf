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
int Findmax(linklist l)
{
    if (l->next == NULL)
        return l->data;
    else return l->next->data>Findmax(l->next)? l->next->data : Findmax(l->next);
}
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        linklist l;
        Insert(l, n);
        cout<<Findmax(l)<<endl;
    }
    return 0;
}

