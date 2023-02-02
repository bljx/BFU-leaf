#include<iostream>
using namespace std;
typedef struct Queue
{
    int* size;
    int tag, front, rear;
}queue;
void Insert(queue &q,int n)
{
    q.size = new int[n];
    for (int i = 0; i < n; i++)
        cin >> q.size[i];
    q.tag = 1;
    q.front = q.rear = 0;
}
void Show(queue q,int n)
{
    while ((q.rear + 1) % n != q.front)
    {
        cout << q.size[q.rear] << " ";
        q.rear++;
    }
    cout << q.size[q.rear];
    cout << endl;
}
int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        queue q;
        Insert(q, n);
        Show(q, n);
    }
    return 0;
}
