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
        linklist p=new LNode;
        cin >> p->data;
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
}
float Avg(linklist& l)
{return l->next==NULL?l->data: Avg(l->next)+l->data;}
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        linklist l;
        Insert(l, n);
        printf("%.2f\n", Avg(l->next) / n);
    }
    return 0;
}
