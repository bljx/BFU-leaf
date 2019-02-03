// http://www.bjfuacm.com/problem/258/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000

void swap(char* a, char* b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void reverse(char* str, int* len, int idx) {
    if (idx == *(len) / 2) {
        return;
    } else {
        reverse(str, len, idx + 1);
        swap(str + idx, str + *len - 1 - idx);
    }
}

int main() {
    char* str;
    while (1) {
        str = (char *)calloc(MAXN, sizeof(char));
        scanf("%s", str);
        if (str[0] == '0' && str[1] == '\0') break;
        int len = (int)strlen(str);
        reverse(str, &len, 0);
        printf("%s\n", str);
        free(str);
    }
}
