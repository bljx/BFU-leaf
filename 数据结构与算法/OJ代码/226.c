// http://www.bjfuacm.com/problem/226/

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

List MergeList(List L1, List L2) {
    // tail insert implementation:
    List L3;
    Position p1, p2, p3;
    p1 = L1->next;
    p2 = L2->next;
    p3 = L1;
    L3 = L1;
    L3->next = NULL;

    while (p1 != NULL || p2 != NULL) {
        if (p1 == NULL) {
            p3 = p2;
            p2 = p2->next;
        } else if (p2 == NULL) {
            p3 = p1;
            p1 = p1->next;
        } else if (p1->val <= p2->val) {
            p3 = p1;
            p1 = p1->next;
        } else {
            p3 = p2;
            p2 = p2->next;
        }

        p3->next = L3->next;
        L3->next = p3;
    }
    free(L2);
    return L3;
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
    List L1, L2, L3;
    int size1, size2;
    while (1) {
        scanf("%d %d", &size1, &size2);
        if (size1 == 0 && size2 == 0) break;
        L1 = InitList(L1, size1);
        L2 = InitList(L2, size2);
        L3 = MergeList(L1, L2);
        Position p = L3->next;
        while (p) {
            printf("%d", p->val);
            printf("%s", p->next == NULL ? "\n" : " ");
            p = p->next;
        }
        DestroyList(L3);
    }
}