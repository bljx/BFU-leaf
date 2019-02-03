// http://www.bjfuacm.com/problem/204/

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

    printf("%d\n", L.len);
    for (int i = 0; i < L.len; i++) {
        printf("%s %s %.2f\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);
    }
}