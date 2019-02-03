// http://www.bjfuacm.com/problem/302/

#include <stdio.h>
#include <stdlib.h>

int MainElement(int* A, int len) {
    int count = 1;
    int K = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] == K) {
            count += 1;
        } else {
            if (count > 0) {
                count -= 1;
            } else {
                K = A[i];
                count = 1;
            }
        }
    }
    if (count > 0) {
        count = 0;
        for (int i = 0; i < len; i++) {
            if (A[i] == K) count += 1;
        }
    }
    if (count > len / 2) return K;
    return -1;
}

int main() {
    int len;
    int* arr;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        arr = (int *)calloc(len, sizeof(int));
        for (int i = 0; i < len; i++) scanf("%d", arr + i);
        int ans = MainElement(arr, len);
        printf("%d\n", ans);
        free(arr);
    }
}