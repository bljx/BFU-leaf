// http://www.bjfuacm.com/problem/292/

#include <stdio.h>
#include <stdlib.h>

struct list {
    struct list *next;
    int val;
};

void insert(struct list ***p, int e) {
    struct list *q;
    struct list *t; // traversal

    q = (struct list *)calloc(1, sizeof(*q));
    q->val = e;
    q->next = NULL;

    int pos = e % 13;
    if ((*p)[pos] == NULL) {
        (*p)[pos] = q;
    } else {
        t = (*p)[pos];
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = q;
    }
}

void create(struct list ***p, int n) {
    int e;
    int pos;

    for (int i = 0; i < n; i++) {
        scanf("%d", &e);
        insert(p, e);
    }
}

void clean(struct list ***p) {
    struct list *t = NULL;
    struct list *to_delete = NULL;

    for (int i = 0; i < 13; i++) {
        if ((*p)[i] == NULL) continue;
        t = (*p)[i];
        (*p)[i] = NULL;
        while (t != NULL) {
            to_delete = t;
            t = t->next;
            free(to_delete);
        }
    }
}

void print(struct list **p) {
    struct list *t;

    for (int i = 0; i < 13; i++) {
        if (p[i] == NULL) printf("%d\n", i);
        else {
            printf("%d ", i);
            t = p[i];
            while (t != NULL) {
                printf("%d%s", t->val, t->next == NULL? "\n": " ");
                t = t->next;
            }
        }
    }
}


int main() {
    struct list (**p) = (struct list **)calloc(13, sizeof(*p));
    int n;
    int key;

    while (1) {
        clean(&p);
        scanf("%d", &n);
        if (n == 0) break;
        create(&p, n);
        scanf("%d", &key);
        insert(&p, key);
        print(p);
    }
}