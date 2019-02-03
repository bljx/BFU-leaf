// http://www.bjfuacm.com/problem/301/

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void reverse(int* arr, int l, int r) {
    int len = r - l + 1;
    for (int i = 0; i < len / 2; i++) {
        swap(arr + l + i, arr + r -i);
    }

}

int main() {
    int len;
    int* arr;
    int x;
    while (1) {
        scanf("%d", &len);
        if (len == 0) break;
        arr = (int *)calloc(len, sizeof(int));
        for (int i = 0; i < len; i++) scanf("%d", arr + i);
        scanf("%d", &x);
        reverse(arr, 0, len - 1);
        reverse(arr, 0, len - 1 - x);
        reverse(arr, len - x, len - 1);
        for (int i = 0; i < len; i++) printf("%d%s", *(arr + i), i == len - 1 ? "\n" : " ");
        free(arr);
    }
}