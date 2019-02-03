// http://www.bjfuacm.com/problem/238/

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node LinkedList;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef char ElementType;

struct Node {
    ElementType val;
    Position next;
};

List InitList(List L, int len) {
    L = (PtrToNode)calloc(1, sizeof(LinkedList));
    L->next = NULL;
    Position p;
    for (int i = 0; i < len; i++) {
        p = (PtrToNode)calloc(1, sizeof(LinkedList));
//        getchar();
        scanf(" %c", &p->val);
        p->next = L->next;
        L->next = p;
    }
    return L;
}

Position FindSuffix(List L1, List L2) {
    Position p1 = L1;
    Position p2 = L2;
    while (p1->next != NULL && p2->next != NULL) {
        if (p1->next->val == p2->next->val) {
            p1 = p1->next;
            p2 = p2->next;
        } else {
            return p1;
        }
    }
    return p1;
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
    int len1, len2;
    List L1, L2;
    while (1) {
        scanf("%d %d", &len1, &len2);
        if (len1 == 0 && len2 ==0) break;
        L1 = InitList(L1, len1);
        L2 = InitList(L2, len2);
        Position p = FindSuffix(L1, L2);

        if (p != NULL) printf("%c\n", p->val);
        DestroyList(L1);
        DestroyList(L2);
        free(L1);
        free(L2);

    }
}