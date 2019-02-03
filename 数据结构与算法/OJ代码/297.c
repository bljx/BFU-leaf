// http://www.bjfuacm.com/problem/261/

#include <stdio.h>

void swap(int* a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void arrange(int* a, int n) {
    int i = 0;
    int j = n - 1;

    while (i < j) {
        while (i < j && a[i] < 0) i++;
        while (i < j && a[j] > 0) j--;
        if (i < j) {
            swap(a + i, a + j);
            i += 1;
            j -= 1;
        }
    }
}

int main() {
    int n;
    int a[105];
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        arrange(a, n);
        for (int i = 0; i < n; i++)
            printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    }
}