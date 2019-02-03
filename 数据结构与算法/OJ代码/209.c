// http://www.bjfuacm.com/problem/209/

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
    int amount;
    scanf("%d", &amount);

    for (int i = 0; i < amount; i++) {
        scanf("%s %s %f", L.elem[i].no, L.elem[i].name, &L.elem[i].price);
        L.len += 1;
    }

    int query;
    scanf("%d", &query);
    while (query--) {
        char* test = (char *)malloc(50 * sizeof(char));
        int* ans = (int *)malloc(amount * sizeof(int));
        memset(ans, 0, sizeof(int));
        memset(test, '\0', sizeof(char));
        scanf("%s", test);
        int count = 0;
        for (int i = 0; i < amount; i++) {
            if (strcmp(test, L.elem[i].name) == 0) {
                ans[count] = i;
                count += 1;
            }
        }
        
        if (count == 0) {
            printf("%s\n", "Sorry，there is no your favourite!");
        } else {
            printf("%d\n", count);
            for (int i = 0; i < count; i++) {
                printf("%s %s %.2f\n", L.elem[ans[i]].no, L.elem[ans[i]].name, L.elem[ans[i]].price);
            }
        }

        free(test);
        free(ans);
    }
}