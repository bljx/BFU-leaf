// http://www.bjfuacm.com/problem/227/

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

List SetList(List L1, List L2) {
    Position p1 = L1->next;
    Position p2 = L2->next;
    Position to_delete;
    List L3 = L1;
    Position p3 = L1;

    while (p1 != NULL && p2 != NULL) {
        if (p1->val == p2->val) {
            p3->next = p1;
            p3 = p3->next;
            p1 = p1->next;

            to_delete = p2;
            p2 = p2->next;
            free(to_delete);
        } else if (p1->val < p2->val) {
            to_delete = p1;
            p1 = p1->next;
            free(to_delete);
        } else {
            // if (p1->val > p2->val) {}
            to_delete = p2;
            p2 = p2->next;
            free(to_delete);
        }
    }
    p3->next = NULL;

    while (p1 != NULL) {
        to_delete = p1;
        p1 = p1->next;
        free(to_delete);
    }
    while (p2 != NULL) {
        to_delete = p2;
        p2 = p2->next;
        free(to_delete);
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
        L3 = SetList(L1, L2);
        Position p = L3->next;
        while (p) {
            printf("%d", p->val);
            printf("%s", p->next == NULL ? "\n" : " ");
            p = p->next;
        }
        DestroyList(L3);
    }
}