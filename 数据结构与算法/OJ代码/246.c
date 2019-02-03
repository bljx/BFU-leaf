// http://www.bjfuacm.com/problem/246/

#include <stdio.h>
#include <stdlib.h>

struct LinkList;
typedef struct LinkList* PtrToList;
typedef struct LinkList* List;
typedef PtrToList Position;

struct LinkList {
    struct LinkList* next;
    int val;
};

void CreateCircular(List* L, int len) {
    struct LinkList dummy;
    dummy.next = NULL;
    Position prev = &dummy;
    Position p;
    for (int i = 0; i < len; i++) {
        int t;
        scanf("%d", &t);
        p = (PtrToList)calloc(1, sizeof(int));
        p->val = t;
        prev->next = p;
        prev = p;
    }
    prev->next = dummy.next;
    (*(L)) = prev;
}


int main() {
    int len, front;
    while (1) {
        scanf("%d %d", &len, &front);
        if (len == 0 && front == 0) break;
        List L;
        CreateCircular(&L, len);
        Position p = L;
        for (int i = 0; i < front; i++) {
            printf("%d ", p->next->val);
            Position to_delete = p->next;
            p->next = to_delete->next;
            free(to_delete);
        }

        printf("%d\n", front == len ? 0 : 1);
    }
}
