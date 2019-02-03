// http://www.bjfuacm.com/problem/206/

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
    float avg = 0.0;

    for (int i = 0; ; i++) {
        scanf("%s %s %f", L.elem[i].no, L.elem[i].name, &L.elem[i].price);
        if (L.elem[i].no[0] == '0' && L.elem[i].name[0] == '0' && L.elem[i].price == 0) {
            break;
        } else {
            avg += L.elem[i].price;
            L.len += 1;
        }
    }

    avg /= L.len;
    for (int i = 0; i < L.len; i++) {
        L.elem[i].price *= (L.elem[i].price < avg) ? 1.2 : 1.1;
    }

    printf("%.2f\n", avg);
    for (int i = 0; i < L.len; i++) {
        printf("%s %s %.2f\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);
    }
}