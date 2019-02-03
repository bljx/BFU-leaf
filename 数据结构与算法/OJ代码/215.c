// http://www.bjfuacm.com/problem/215/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OVERFLOW 11

struct Books;
typedef struct Books Book;
typedef struct Books* PtrToBook;
typedef PtrToBook List;
typedef PtrToBook Position;

struct Books {
    char no[20];
    char name[50];
    float price;
    struct Books* next;
};

List swap(Position prev, Position i) {
    prev->next = i->next;
    i->next = i->next->next;
    prev->next->next = i;
    return prev->next;
}

void BubbleSort(List L) {
    Position i, prev;
    Position end = NULL;
    while (L->next->next != end) {
        i = L->next;
        prev = L;
        while (i->next != end) {
            if (i->price < i->next->price || (i->price == i->next->price &&
                                              strcmp(i->name, i->next->name) < 0)) {
                i = swap(prev, i);
                // DANGER:
                // use double pointer, or return Type* to reset i
            }
            i = i->next;
            prev  = prev->next;
        }
        end = i;
    }
}

void InitList(List* L) {
    *L = (PtrToBook)calloc(1, sizeof(Book));
    if (!*L) exit(OVERFLOW);
    (*L)->next = NULL;
    return;
}


int main() {
    List L;
    InitList(&L);
    int count = 0;
    Position post, pre;

    while (1) {
        post = (PtrToBook)calloc(1, sizeof(Book));
        if (!post) exit(OVERFLOW);
        scanf("%s %s %f", post->no, post->name, &post->price);
        if (post->no[0] == '0' && post->name[0] == '0' && post->price == 0) {
            free(post);
            break;
        } else if (count == 0) {
            L->next = post;
        } else {
            pre->next = post;
        }
        pre = post;
        count += 1;
    }
    pre->next = NULL;

    BubbleSort(L);
    Position p = L->next;
    while (p) {
        printf("%s %s %.2f\n", p->no, p->name, p->price);
        p = p->next;
    }
}
