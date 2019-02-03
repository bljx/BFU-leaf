// http://www.bjfuacm.com/problem/241/

#include <stdio.h>
#include <stdlib.h>

#define OUT_OF_MEMORY (12)
#define DENIED (13)
#define loop(n) for (int i = 0; i < n; i++)
#define SElemType int

typedef struct {
    int top[2], bot[2]; // "pointer to top and base"
    SElemType* V; // stack array
    int m; // capacity
} DblStack;

typedef DblStack* Stack;

Stack InitDblStack(Stack S, int m) {
    S = calloc(1, sizeof(DblStack));
    S->V = calloc(m, sizeof(SElemType));
    S->bot[0] = -1;
    S->bot[1] = m;
    S->top[0] = -1;
    S->top[1] = m;
    return S;
}

int IsFull(Stack S) {
    if (S->top[1] - S->top[0] == 1) return 1;
    return 0;
}

int IsEmpty(Stack S, int i) {
    return S->top[i] == S->bot[i];
}

void DblPush(Stack S, int i, int x) {
    if (IsFull(S)) exit(OUT_OF_MEMORY);
    if (i == 0) {
        S->V[++S->top[0]] = x;
    } else {
        S->V[--S->top[1]] = x;
    }
}

void DblPop(Stack S, int i, SElemType* x) {
    if (IsEmpty(S, i)) exit(DENIED);
    if (i == 0) {
        *x = S->V[S->top[0]--];
    } else {
        *x = S->V[S->top[1]++];
    }
}


int main() {
    int m;
    int e0, e1, d0, d1;
    int x;
    Stack S;
    while (1) {
        scanf("%d", &m);
        if (m == 0) break;
        S = InitDblStack(S, m);
        scanf("%d %d %d %d", &e0, &e1, &d0, &d1);
        loop(e0) {
            scanf("%d", &x);
            DblPush(S, 0, x);
        }
        loop(e1) {
            scanf("%d", &x);
            DblPush(S, 1, x);
        }
        printf("%d\n", (m == e0 + e1) ? 1 : 0);
        loop(d0) {
            int o;
            DblPop(S, 0, &o);
            printf("%d ", o);
        }
        printf("%d\n", !IsEmpty(S, 0));
        loop(d1) {
            int o;
            DblPop(S, 1, &o);
            printf("%d ", o);
        }
        printf("%d\n", !IsEmpty(S, 1));

    }
}
