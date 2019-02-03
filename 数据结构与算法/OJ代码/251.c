// http://www.bjfuacm.com/problem/251/

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node LinkedList;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node {
    ElementType val;
    Position next;
};

List InitList(List L, int len) {
    L = (PtrToNode)calloc(1, sizeof(LinkedList));
    L->next = NULL;
    List prev = L;
    List post;
    for (int i = 0; i < len; i++) {
        post = (PtrToNode)calloc(1, sizeof(LinkedList));
        scanf("%d", &post->val);
        post->next = NULL;
        prev->next = post;
        prev = post;
    }
    return L;
}

void DestroyList(List L) {
    Position p;
    p = L->next;
    L->next = NULL;
    while (p != NULL) {
        free(p);
        p = p->next;
    }
}

int FindMax(Position p) {
    if (!p->next) return p->val;
    else {
        int t = FindMax(p->next);
        return p->val > t ? p->val : t;
    }
}

int main() {
    int len;
    List L;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        L = InitList(L, len);
        Position p = L->next;
        printf("%d\n", FindMax(p));
        DestroyList(L);
        free(L);
    }
}
