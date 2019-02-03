// http://www.bjfuacm.com/problem/217/

#include <stdio.h>
#include <stdlib.h>
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

List Reverse(List L) {
    // SEE: gorgeous solve!
    // https://www.geeksforgeeks.org/reverse-a-linked-list/
    Position cur = L->next;
    free(L);
    Position prev = NULL;
    Position next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    List NewL = (PtrToBook)calloc(1, sizeof(Book));
    NewL->next = prev;
    return NewL;
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

    L = Reverse(L);
    Position p = L->next;
    while (p) {
        printf("%s %s %.2f\n", p->no, p->name, p->price);
        p = p->next;
    }
}