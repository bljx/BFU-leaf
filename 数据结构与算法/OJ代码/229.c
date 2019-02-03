// http://www.bjfuacm.com/problem/229/

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

List* DecomposeList(List L) {
    List* lists = (PtrToNode *)calloc(2, sizeof(PtrToNode));
    List L1 = (PtrToNode)calloc(1, sizeof(LinkedList));
    List L2 = (PtrToNode)calloc(1, sizeof(LinkedList));

    Position p1, p2;
    Position prev1, prev2;
    prev1 = L1;
    prev2 = L2;
    L1->next = p1;
    L2->next = p2;
    Position p = L->next;
    while (p) {
        if (p->val < 0) {
            p1 = (PtrToNode)calloc(1, sizeof(LinkedList));
            p1->next = NULL;
            p1->val = p->val;
            prev1->next = p1;
            prev1 = p1;
        } else if (p->val > 0) {
            p2 = (PtrToNode)calloc(1, sizeof(LinkedList));
            p2->next = NULL;
            p2->val = p->val;
            prev2->next = p2;
            prev2 = p2;
        }
        p = p->next;
    }

    lists[0] = L1;
    lists[1] = L2;

    return lists;
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

void PrintList(List L) {
    Position p = L->next;
    while (p) {
        printf("%d", p->val);
        printf("%s", p->next == NULL ? "\n" : " ");
        p = p->next;
    }
}

int main() {
    List L;
    List L1, L2;
    int len;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        L = InitList(L, len);
        List* lists = DecomposeList(L);
        L1 = lists[0];
        L2 = lists[1];
        PrintList(L1);
        PrintList(L2);
        DestroyList(L1);
        DestroyList(L2);
    }
}

