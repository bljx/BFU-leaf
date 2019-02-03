// http://www.bjfuacm.com/problem/220/

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

void InitList(List* L) {
    *L = (PtrToBook)calloc(1, sizeof(Book));
    if (!*L) exit(OVERFLOW);
    (*L)->next = NULL;
    return;
}

Position Find(List L, int index) {
    if (!L || !L->next) return NULL;
    Position p = NULL;
    for (int i = 0; i < index; i++) {
        p = i == 0 ? L->next : p->next;
        if (p == NULL) return NULL;
    }
    return p;
}


int main() {
    List L;
    InitList(&L);

    int count;
    Position post, pre;
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        post = (PtrToBook)calloc(1, sizeof(Book));
        if (!post) exit(OVERFLOW);
        scanf("%s %s %f", post->no, post->name, &post->price);
        if (i == 0) {
            L->next = post;
        } else {
            pre->next = post;
        }
        pre = post;
    }
    pre->next = NULL;

    int query, inquiry;
    scanf("%d", &query);
    while (query--) {
        Position i = (PtrToBook)calloc(1, sizeof(Book));
        scanf("%d", &inquiry);
        i = Find(L, inquiry);
        if (!i) {
            printf("%s\n", "Sorry，the book on the best position doesn't exist!");
        } else {
            printf("%s %s %.2f\n", i->no, i->name, i->price);
        }
        free(i);
    }
}