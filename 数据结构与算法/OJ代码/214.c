// http://www.bjfuacm.com/problem/214/

// GUIDE:
// https://stackoverflow.com/questions/2605476/calloc-v-s-malloc-and-time-efficiency

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
    // L = InitList(L) is also accepted
    // SEE:
    // https://curl.haxx.se/libcurl/c/curl_slist_append.html
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

    printf("%d\n", count);
    Position p = L->next;
    while (p) {
        printf("%s %s %.2f\n", p->no, p->name, p->price);
        p = p->next;
    }
}