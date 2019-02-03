// http://www.bjfuacm.com/problem/239/

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
    Position prev = L;
    Position post;
    for (int i = 1; i <= len; i++) {
        post = (PtrToNode)calloc(1, sizeof(LinkedList));
        prev->next = post;
        post->val = i;
        post->next = L->next;
        prev = post;
    }
    free(L);
    return prev;
}

Position DeleteList(Position prev) {
    if (prev->next == prev) {
        free(prev->next);
        return NULL;
    } else {
        Position to_delete = prev->next;
        prev->next = to_delete->next;
        free(to_delete);
        return prev;
    }
}

void PrintNode(Position p) {
    if (p->next == p) {
        printf("%d\n", p->val);
    } else {
        printf("%d ", p->val);
    }
}

void Traversal(List p, int s) {
    while (1) {
        for (int i = 0; i < s - 1; i++) p = p->next;
        PrintNode(p->next);
        p = DeleteList(p);
        if (p == NULL) break;
    }

}


int main() {
    int step;
    int len;
    List L;
    while (1) {
        // use previous to traverse and delete
        scanf("%d %d", &len, &step);
        if (len == 0 && step == 0) break;
        Position p = InitList(L, len);
        Traversal(p, step);
    }
}