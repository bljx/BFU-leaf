// http://www.bjfuacm.com/problem/234/

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

Position Delete(Position prev) {
    Position to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
    return prev;
}

//Position FindPrev(List L, Position p) {
//    Position prev = L;
//    while (prev->next != p) {
//        prev = prev->next;
//    }
//    return prev;
//}

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
    int target;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        L = InitList(L, len);
        scanf("%d", &target);
        Position prev = L;
        Position p;
        while (prev->next != NULL) {
            // if (p->val == target) p = Delete(FindPrev(L, p));
            if (prev->next->val == target) {
                prev = Delete(prev);
            } else {
                prev = prev->next;
            }
        }
        p = L->next;
        while (p) {
            printf("%d", p->val);
            printf("%s", p->next == NULL ? "\n" : " ");
            p = p->next;
        }
        DestroyList(L);
        free(L);
    }
}