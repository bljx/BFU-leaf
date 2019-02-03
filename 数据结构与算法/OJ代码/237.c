// http://www.bjfuacm.com/problem/237/

#include <stdio.h>
#include <stdlib.h>

int SearchMid(int* A, int* B, int n) {
    int start1 = 0;
    int end1 = n - 1;
    int start2 = 0;
    int end2 = n - 1;

    while (start1 != end1 || start2 != end2) {
        int m1 = (start1 + end1) / 2;
        int m2 = (start2 + end2) / 2;

        if (A[m1] == B[m2]) {
            return A[m1];
        } else if (A[m1] < B[m2]) {
            if ((start1 + end1) % 2 == 0) {
                start1 = m1;
                end2 = m2;
            } else {
                start1 = m1 + 1;
                end2 = m2;
            }
        } else {
            // A[m1] > B[m2]
            if ((start1 + end1) % 2 == 0) {
                end1 = m1;
                start2 = m2;
            } else {
                end1 = m1;
                start2 = m2 + 1;
            }
        }
    }
    return A[start1] < B[start2] ? A[start1] : B[start2];
}


int main() {
    int len;
    int* a;
    int* b;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        a = (int *)calloc(len, sizeof(int));
        b = (int *)calloc(len, sizeof(int));
        for (int i = 0; i < len; i++) scanf("%d", a + i);
        for (int i = 0; i < len; i++) scanf("%d", b + i);
        int ans = SearchMid(a, b, len);
        printf("%d\n", ans);
        free(a);
        free(b);
    }
}