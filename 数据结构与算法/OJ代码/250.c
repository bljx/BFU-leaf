// http://www.bjfuacm.com/problem/250/

// https://codegolf.stackexchange.com/questions/40141/the-ackermann-function

/**********************
 * ACKERMANN FUNCTION *
 *   NON-RECURSIVE    *
 *   IMPLEMENTATION   *
 **********************/

/* AC: CPP

#include <iostream>
#include <stack>
using namespace std;

int ack(int m, int n) {
    stack<int> s;
    s.push(m);
    while (!s.empty()) {
        m = s.top();
        s.pop();
        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            n = 1;
            s.push(m - 1);
        } else {
            n = n - 1;
            s.push(m - 1);
            s.push(m);
        }
    }
    return n;
}
int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        cout << ack(m, n) << endl;
    }

}

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000

int Ack(int m, int n) {
    int* stack = (int *)calloc(MAXN, sizeof(int));
    int i = 0;
    stack[++i] = m;
    while (i != 0) {
        m = stack[i--];
        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            n = 1;
            stack[++i] = m - 1;
        } else {
            n = n - 1;
            stack[++i] = m - 1;
            stack[++i] = m;
        }
    }
    free(stack);
    return n;
}


int main() {
    int m, n;
    while (1) {
        scanf("%d %d", &m, &n);
        if (m == 0 && n == 0) break;
        printf("%d\n", Ack(m, n));
    }
}
