// http://www.bjfuacm.com/problem/243/

#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

struct StackRecord {
    int* array;
    int top;
    int cap;
};
typedef struct StackRecord* Stack;

Stack InitStack(Stack S) {
    S = malloc(sizeof(struct StackRecord));
    S->array = calloc(MAXN, sizeof(int));
    S->top = -1;
    S->cap = MAXN;
    return S;
}

void Push(Stack S, int e) {
    if (S->top + 1 == S->cap) exit(12);
    S->array[++S->top] = e;
}

int Pop(Stack S, int* t) {
    if (S->top == -1) return 0;
    *t = S->array[S->top--];
    return 1;
}

int main() {
    Stack S;
    S = InitStack(S);
    int n;
    while (scanf("%d", &n) && n) {
        int query;
        while (n--) {
            scanf("%d", &query);
            if (query == -1) {
                int t;
                if (Pop(S, &t)) printf("%d\n", t);
                else {
                    printf("%s\n", "POP ERROR");
                    while (n--) {
                        scanf("%d", &query);
                    }
                    break;
                }
            } else {
                Push(S, query);
            }
        }
        S->top = -1;
    }
}
