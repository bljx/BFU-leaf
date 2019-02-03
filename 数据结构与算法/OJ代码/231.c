// http://www.bjfuacm.com/problem/231/

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

List Reverse(List L) {
    Position cur = L->next;
    free(L);
    Position prev = NULL;
    Position next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    List NewL = (PtrToNode)calloc(1, sizeof(LinkedList));
    NewL->next = prev;
    return NewL;
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


int main() {
    List L;
    int len;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        L = InitList(L, len);
        L = Reverse(L);
        Position p = L->next;
        while (p) {
            printf("%d", p->val);
            printf("%s", p->next == NULL ? "\n" : " ");
            p = p->next;
        }
        DestroyList(L);
        free(L);
    }
}