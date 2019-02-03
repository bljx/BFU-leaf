// http://www.bjfuacm.com/problem/260/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 10005

int main() {
    int x, y;
    bool* t;
    int flag;
    while (1) {
        scanf("%d %d", &x, &y);
        if (x == 0 && y == 0) break;
        flag = 0;
        t = (bool *)calloc(MAXN, sizeof(bool));
        int s;
        for (int i = 0; i < x * y; i++) {
            scanf("%d", &s);
            if (t[s] == 1) {
                flag = 1;
            } else {
                t[s] = 1;
            }
        }
        printf("%s\n", flag == 0 ? "NO" : "YES");
        free(t);
    }
}