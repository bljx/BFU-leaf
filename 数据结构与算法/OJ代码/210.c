// http://www.bjfuacm.com/problem/210/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000
#define OVERFLOW 11

typedef struct Books Book;
typedef struct SqLists SqList;

struct Books {
    char no[20];
    char name[50];
    float price;
};

struct SqLists {
    struct Books* elem;
    int len;
};

void InitList(SqList* L) {
    L->elem = (Book *)calloc(MAXSIZE, sizeof(Book));
    if (!L->elem) exit(OVERFLOW);
    L->len = 0;
    return;
}

int isValid(SqList* L, int index) {
    return (index <= L->len && index >= 1);
}

void CopyBook(Book* d, Book* s) {
    strcpy(d->no, s->no);
    strcpy(d->name, s->name);
    d->price = s->price;
}

void GetElem(SqList* L, int index, Book* p) {
    if (!isValid(L, index)) {
        printf("%s\n", "Sorry，the book on the best position doesn't exist!");
    } else {
        CopyBook(p, &(L->elem[index - 1]));
    }
}

void ZeroBook(Book* p) {
    memset(p->no, '\0', sizeof(char));
    memset(p->name, '\0', sizeof(char));
    p->price = 0.0;
}


int main() {
    SqList L;
    InitList(&L);
    int amount;
    scanf("%d", &amount);

    for (int i = 0; i < amount; i++) {
        scanf("%s %s %f", L.elem[i].no, L.elem[i].name, &L.elem[i].price);
        L.len += 1;
    }

    int query;
    scanf("%d", &query);
    while (query--) {
        int index;
        scanf("%d", &index);
        Book* p = (Book *)malloc(sizeof(Book));
        ZeroBook(p);
        GetElem(&L, index, p);
        if (isValid(&L, index)) {
            printf("%s %s %.2f\n", p->no, p->name, p->price);
        }
        free(p);
    }
}