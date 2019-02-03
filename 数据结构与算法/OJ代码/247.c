// http://www.bjfuacm.com/problem/247/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* base;
    int front, rear;
    int tag;
} Queue;

void Create(Queue* Q, int len) {
    Q->base = calloc(len, sizeof(int));
    if (!Q->base) exit(12);
    (*Q).front = (*Q).rear = 0;
    (*Q).tag = 0;
}

void enqueue(Queue* Q, int e, int n) {
    if ((Q->tag == 1) && (Q->rear == Q->front)) exit(12);
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % n;
    if (Q->tag == 0) Q->tag = 1;
}

int dequeue(Queue* Q, int n) {
    if ((Q->tag == 0) && (Q->rear == Q->front)) exit(13);
    int ans = Q->base[Q->front];
    Q->front = (Q->front + 1) % n;
    if (Q->tag == 1) Q->tag = 0;
    return ans;
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        Queue Q;
        Create(&Q, n);
        int a;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            enqueue(&Q, a, n);
        }
        for (int i = 0; i < n; i++) {
            printf("%d%s", dequeue(&Q, n), i == n - 1 ? "\n" : " ");
        }
    }
}

