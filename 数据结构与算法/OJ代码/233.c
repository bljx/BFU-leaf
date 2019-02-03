// http://www.bjfuacm.com/problem/233/

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
    Position pre;
};

List InitDoublyList(List L, int len) {
    LinkedList dummy;
    Position p = dummy.next;
    Position prev = &dummy;
    for (int i = 0; i < len; i++) {
        p = (PtrToNode)calloc(1, sizeof(LinkedList));
        prev->next = p;
        p->pre = prev;
        prev = prev->next;
        scanf("%d", &p->val);
    }
    p->next = dummy.next;
    dummy.next->pre = p;
    return dummy.next;
}

List SwapPrev(List L, int x) {
    Position p = L;
    for (int i = 0; i < x - 1; i++) p = p->next;
    Position ans;
    if (p == L) {
        ans = p->pre;
    } else if (L->next == p) {
        ans = p;
    } else {
        ans = L;
    }

    Position left = p->pre->pre;
    Position right = p->next;
    left->next = p;
    right->pre = p->pre;
    Position prev = p->pre;
    prev->next = right;
    p->pre = left;
    prev->pre = p;
    p->next = prev;

    return ans;
}

void DestroyList(List L) {
    Position p;
    p = L;
    while (1) {
        free(p);
        p = p->next;
        if (p == L) break;
    }
}


int main() {
    int len;
    List L;
    int x;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        L = InitDoublyList(L, len);
        scanf("%d", &x);
        L = SwapPrev(L, x);
        Position p = L;
        while (1) {
            printf("%d", p->val);
            printf("%s", p->next == L ? "\n" : " ");
            p = p->next;
            if (p == L) break;
        }
        DestroyList(L);
    }
}