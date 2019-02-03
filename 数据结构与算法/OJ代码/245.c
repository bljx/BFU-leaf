// http://www.bjfuacm.com/problem/245/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char* a;
    int stack;
    while (1) {
        a = calloc(80, sizeof(char));
        scanf("%s", a);
        if (a[0] == '0') break;
        stack = 0;
        int flag = 1;
        // default legal
        for (int i = 0; i < strlen(a); i++) {
            if (a[i] == 'I') {
                stack++;
            } else if (!stack) {
                flag = 0;
            } else {
                stack--;
            }
        }
        if (stack) flag = 0;
        printf("%s\n", flag ? "TRUE" : "FALSE");
        free(a);
    }
}