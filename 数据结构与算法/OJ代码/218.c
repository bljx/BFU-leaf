// http://www.bjfuacm.com/problem/218/

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


int main() {
    List L;
    InitList(&L);

    int count;
    float max;
    Position post, pre;
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        post = (PtrToBook)calloc(1, sizeof(Book));
        if (!post) exit(OVERFLOW);
        scanf("%s %s %f", post->no, post->name, &post->price);
        if (i == 0) {
            L->next = post;
            max = post->price;
        } else {
            pre->next = post;
            max = max < post->price ? post->price : max;
        }
        pre = post;
    }
    pre->next = NULL;

    int cnt = 0;
    Position p = L->next;
    PtrToBook* ans = (PtrToBook*)calloc(count, sizeof(PtrToBook));
    while (p) {
        if (p->price == max) {
            ans[cnt] = p;
            cnt += 1;
        }
        p = p->next;
    }

    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%s %s %.2f\n", (*(ans + i))->no, (*(ans + i))->name, (*(ans + i))->price);
    }
}