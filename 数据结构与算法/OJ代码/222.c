// http://www.bjfuacm.com/problem/222/

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

int Delete(List L, int index) {
    if (!L || index < 1) return 0;
    Position prev = L;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
        if (prev->next == NULL)
            return 0;
    }
    Position to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
    return 1;
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

    int index;
    scanf("%d", &index);
    if (Delete(L, index)) {
        Position p = L->next;
        while (p) {
            printf("%s %s %.2f\n", p->no, p->name, p->price);
            p = p->next;
        }
    } else {
        printf("%s\n", "Sorry，the position to be deleted is invalid!");
    }
}
