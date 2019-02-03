// http://www.bjfuacm.com/problem/295/

#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    struct LinkedList *next;
    struct LinkedList *prev;
    int val;
};

typedef struct LinkedList LinkedList;
typedef LinkedList *PtrToList;
typedef PtrToList List;
typedef PtrToList Position;

List BuildList(int );
void PrintNode(List );
List BubbleSort(List , int );

int main()
{
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        List L = BuildList(n);
        L = BubbleSort(L, n);
        PrintNode(L);
    }
}

List BuildList(int n)
{
    LinkedList dummy;
    dummy.next == NULL;

    Position p; // for every new nodes
    Position q = &dummy; // for the previous node to assign
    int val;

    for (int i = 0; i < n; i++) {
        p = (LinkedList *)calloc(1, sizeof(*p));
        scanf("%d", &val);
        p->val = val;

        q->next = p;
        p->prev = q;
        p->next = NULL;
        q = p;
    }

    dummy.next->prev = NULL;
    return dummy.next;
}

void PrintNode(List L)
{
    Position p = L;
    while (p != NULL) {
        printf("%d%s", p->val, p->next == NULL? "\n": " ");
        p = p->next;
    }
}

List BubbleSort(List L, int n)
{
    LinkedList dummy;
    dummy.next = L;
    L->prev = &dummy;

    Position end = NULL;
    int swapped;

    do {
        swapped = 0;
        Position p = dummy.next;
        while (p->next != end) {
            if (p->val > p->next->val) {
                swapped = 1;

                // swap here:
                Position l = p->prev;
                Position r = p->next->next;

                Position p1 = p;
                Position p2 = p->next;

                l->next = p2;
                p2->prev = l;

                p2->next = p1;
                p1->prev = p2;

                p1->next = r;
                if (r != NULL) r->prev = p1;
            } else {
                p = p->next;
            }
        }
        end = p;

    } while (swapped);

    return dummy.next;
}
