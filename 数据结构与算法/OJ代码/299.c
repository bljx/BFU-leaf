// http://www.bjfuacm.com/problem/299/

#include <stdio.h>
#include <string.h>

int main() {
    int a[200];
    int b[200];
    int c[200];
    int n;
    while (1) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[j] < a[i]) {
                    b[i]++;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            c[b[i]] = a[i];
        }
        for (int i = 0; i < n; i++) {
            printf("%d%s", c[i], i == n - 1? "\n": " ");
        }

    }
}