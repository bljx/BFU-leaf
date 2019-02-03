// http://www.bjfuacm.com/problem/207/

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

void swap(Book* a, Book* b) {
    Book t = *a;
    *a = *b;
    *b = t;
}

void reverse(SqList* L, int len) {
    for (int i = 0; i < len / 2; i++) {
        swap(L->elem + i, L->elem + len - i - 1);
    }
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

    reverse(&L, amount);

    for (int i = 0; i < L.len; i++) {
        printf("%s %s %.2f\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);
    }
}