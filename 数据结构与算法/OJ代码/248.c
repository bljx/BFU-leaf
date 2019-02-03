// http://www.bjfuacm.com/problem/248/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* base;
    int rear, front;
} Queue;

void Create(Queue* Q, int len) {
    Q->base = calloc(len + 1, sizeof(int));
    if (!Q->base) exit(12);
    (*Q).rear = (*Q).front = 0;
}

void enqueue(Queue* Q, int e, int n) {
    if ((Q->front + 1) % (n + 1) == Q->rear) exit(12);
    Q->base[Q->front] = e;
    Q->front = (Q->front + 1) % (n + 1);
}

int dequeue(Queue* Q, int n) {
    if (Q->front == Q->rear) exit(13);
    int ans = Q->base[Q->rear];
    Q->rear = (Q->rear + 1) % (n + 1);
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

