// http://www.bjfuacm.com/problem/259/

#include <stdio.h>
#include <stdlib.h>
#define MAXN 10005

int strlen(char* a) {
    int i = 0;
    while ((*(a + i)) != '\0') { i += 1; }
    return i;
}

void swap(char* a, char* b) {

    char t = *a;
    *a = *b;
    *b = t;
}

void reverse(char* str, int start, int end) {
    // start end is position not index
    int len = end - start + 1;
    if (len <= 1) return;
    str += (start - 1);
    for (int i = 0; i < len / 2; i++) {
        swap(str + i, str + len - i - 1);
    }
}

void insert(char* s, char* t, int pos) {
    // s ------> t
    //   insert
    int s_len = strlen(s);
    int t_len = strlen(t);
    for (int i = 0; i < s_len; i++) {
        *(t + t_len + i) = *(s + i);
    }
    reverse(t, pos, s_len + t_len);
    reverse(t, pos, pos + s_len - 1);
    reverse(t, pos + s_len, s_len + t_len);
}

void wash(char* s) {
    for (int i = 0; i < MAXN; i++) *(s + i) = '\0';
}


int main() {
    int pos;

    while (1) {
        char s[MAXN];
        char t[MAXN]; // to be inserted

        scanf("%d", &pos);
        if (pos == 0) break;
        scanf("%s", t);
        scanf("%s", s);
        insert(s, t, pos);
        printf("%s\n", t);

        wash(s);
        wash(t);
    }
}