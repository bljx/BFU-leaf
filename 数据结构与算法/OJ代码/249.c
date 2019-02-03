// http://www.bjfuacm.com/problem/249/

#include <stdio.h>

int Ack(int m, int n) {
    if (m == 0) return n + 1;
    else if (n == 0) return Ack(m - 1, 1);
    else return Ack(m - 1, Ack(m, n - 1));
}

int main() {
    int m, n;
    while (1) {
        scanf("%d %d", &m, &n);
        if (m == 0 && n == 0) break;
        printf("%d\n", Ack(m, n));
    }
}
