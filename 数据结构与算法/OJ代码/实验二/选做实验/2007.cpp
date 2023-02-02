#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}*linklist, LNode;
linklist Insert(linklist& l,int n)
{
    l = new LNode;
    l->next = NULL;
    cin >> l->data;
    linklist rear=l;
    for (int i = 1; i < n; i++)
    {
        linklist p = new LNode;
        cin >> p->data;
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    rear->next = l;
    return rear;
}
void Show(linklist rear,int n,int m)
{
    linklist head = rear->next;
    rear = rear->next;
    int i = 1;
    while (i!=m)
    {
        cout << rear->data << " ";
        rear = rear->next;
        i++;
    }
    cout << rear->data << " ";
    if (m >= n)
        cout << 0 << endl;
    else
        cout << 1 << endl;
}
int main()
{
    int m, n;
    while (cin >> n >> m && m != 0 && n != 0)
    {
        linklist l;
        Show(Insert(l, n), n, m);
    }
    return 0;
}
