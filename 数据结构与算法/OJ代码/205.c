// http://www.bjfuacm.com/problem/205/

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

void BubbleSort(SqList* L) {
    for (int i = 0; i < L->len - 1; i++) {
        for (int j = 0; j < L->len - i - 1; j++) {
            if (L->elem[j].price < L->elem[j + 1].price) {
                swap(L->elem + j, L->elem + j + 1);
            }
        }
    }
}


int main() {
    SqList L;
    InitList(&L);

    for (int i = 0; ; i++) {
        scanf("%s %s %f", L.elem[i].no, L.elem[i].name, &L.elem[i].price);
        if (L.elem[i].no[0] == '0' && L.elem[i].name[0] == '0' && L.elem[i].price == 0) {
            break;
        } else {
            L.len += 1;
        }
    }

    BubbleSort(&L);
    for (int i = 0; i < L.len; i++) {
        printf("%s %s %.2f\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);
    }
}