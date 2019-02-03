// http://www.bjfuacm.com/problem/216/

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

    int count = 0;
    Position post, pre;
    double avg;

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
        avg += post->price;
    }
    pre->next = NULL;

    Position p;
    avg /= count;
    printf("%.2f\n", avg);
    p = L->next;
    while (p) {
        p->price *= (p->price < avg) ? 1.2 : 1.1;
        p = p->next;
    }
    
    p = L->next;
    while (p) {
        printf("%s %s %.2f\n", p->no, p->name, p->price);
        p = p->next;
    }
}