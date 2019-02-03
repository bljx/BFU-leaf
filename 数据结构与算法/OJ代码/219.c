// http://www.bjfuacm.com/problem/219/

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

    int cnt;
    int query;
    scanf("%d", &query);
    while (query--) {
        cnt = 0;
        Position p = L->next;
        PtrToBook* ans = (PtrToBook*)calloc(count, sizeof(PtrToBook));
        char test[50];
        scanf("%s", test);
        while (p) {
            if (!strcmp(p->name, test)) {
                ans[cnt] = p;
                cnt += 1;
            }
            p = p->next;
        }
        if (cnt == 0) {
            printf("%s\n", "Sorry，there is no your favourite!");
        } else {
            printf("%d\n", cnt);
            for (int i = 0; i < cnt; i++) {
                printf("%s %s %.2f\n", (*(ans + i))->no, (*(ans + i))->name, (*(ans + i))->price);
            }
        }
        free(ans);
    }
}