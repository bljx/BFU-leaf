// http://www.bjfuacm.com/problem/261/

#include <stdio.h>
#include <string.h>

#define MAXN 100


int main() {
    int n;
    int a[MAXN];
    int b[MAXN];
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        memset(a, 0, sizeof(int) * MAXN);
        memset(b, 0, sizeof(int) * MAXN);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);

        int i;
        int j = 0;
        for (i = 0; i < n; i++) {
            if (a[i] > 0) b[j++] = a[i];
        }
        for (i = 0; i < n; i++) {
            if (a[i] < 0) b[j++] = a[i];
        }
        for (int i = 0; i < n; i++) {
            printf("%d%s", b[i], i == n - 1 ? "\n" : " ");
        }

    }
}