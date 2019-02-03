// http://www.bjfuacm.com/problem/294/

#include <stdio.h>
#include <stdlib.h>

struct LinkedList;
struct LinkedList {
    struct LinkedList *next;
    int val;
};

typedef struct LinkedList LinkedList;
typedef struct LinkedList *PtrToList;
typedef PtrToList List;
typedef PtrToList Position;

List CreateList(int );
List SelectionSort(List );
void PrintList(List );
void DestroyList(List );
Position GetNode(List * , Position );

int main()
{
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        List L = CreateList(n);
        L = SelectionSort(L);
        PrintList(L);
        DestroyList(L);
    }
}

List CreateList(int n)
{
    struct LinkedList dummy;
    dummy.next = NULL;
    Position p;
    Position pre = &dummy;
    while (n--) {
        p = (PtrToList)calloc(1, sizeof(*p));
        scanf("%d", &(p->val));
        pre->next = p;
        pre = p;
        p->next = NULL;
    }
    return dummy.next;
}

List SelectionSort(List L)
{
    struct LinkedList dummy;
    dummy.next = NULL;
    Position pre = &dummy;


    Position p; // p for traversal and select min and insert to give up order
    struct LinkedList min;
    while (L != NULL) {
        p = L;
        min.next = L;
        min.val = p->val;

        while (p != NULL) {
            if (min.val > p->val) {
                min.next = p;
                min.val = p->val;
            }
            p = p->next;
        }

        p = GetNode(&L, min.next);
        pre->next = p;
        p->next = NULL;
        pre = p;
    }
    return dummy.next;
}

Position GetNode(List *L, Position p)
{
    Position pre; // for choosing previous
    Position l = (*L); // represent (*L)

    struct LinkedList dummy;
    dummy.next = l;
    pre = &dummy;

    while (pre->next != NULL) {
        if (pre->next == p) {
            if (pre == &dummy) {
                (*L) = l->next;
            }
            pre->next = p->next;
            return p;
        } else {
            pre = pre->next;
        }
    }
}

void PrintList(List L)
{
    if (L == NULL) return;
    Position p = L;
    while (p != NULL) {
        printf("%d%s", p->val, p->next == NULL? "\n": " ");
        p = p->next;
    }
}

void DestroyList(List L)
{
    Position to_delete = L;
    if (L->next == NULL) {
        free(L);
    } else {
        Position p = L->next;
        free(to_delete);
        while (p != NULL) {
            to_delete = p;
            p = p->next;
            free(to_delete);
        }
    }
}
