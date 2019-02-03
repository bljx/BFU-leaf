// http://www.bjfuacm.com/problem/296/

#include <stdio.h>

/**
 * 5
 * R W R B R
 *
 * R R R W B
 */

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void arrange(char c[], int n) {
    int i = 0;
    int j = 0;
    int k = n - 1;
    
    while (j <= k) {
        // algorithm: loop White, exchanging Red <- White -> Blue
        if (c[j] == 'R') {
            swap(c + i, c + j);
            i++;
            j++;
        } else if (c[j] == 'W') {
            j++;
        } else { // 'B'
            swap(c + j, c + k);
            k--;
        }
    }
}

int main() {
    int n;
    char arr[200];
    
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 0; i < n; i++) scanf("%s", &arr[i]);
        // %c with input space, %s escape space
        arrange(arr, n);
        for (int i = 0; i < n; i++) printf("%c%s", arr[i], i == n - 1? "\n": " ");
    }
}
