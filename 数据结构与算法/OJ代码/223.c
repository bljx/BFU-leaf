// http://www.bjfuacm.com/problem/223/

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

void Delete(Position prev) {
    if (!prev->next) return;
    Position to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
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

    Position p = L->next;
    while (p->next && p) {
        Position q = p;
        while (q->next && q) {
            if (strcmp(p->no, q->next->no) == 0) {
                // store PtrToBook[] thus avoid influnce on iteration
                Delete(q);
                count -= 1;
            }
            q = q->next;
        }
        p = p->next;
    }

    printf("%d\n", count);
    p = L->next;
    while (p) {
        printf("%s %s %.2f\n", p->no, p->name, p->price);
        p = p->next;
    }
}