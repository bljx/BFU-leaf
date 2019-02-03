// http://www.bjfuacm.com/problem/255/

#include <stdio.h>
#define MAXN 1000

int e;
int flag;
int p[MAXN];
int m[MAXN][3];

void dfs(int n) {
    if (n == e) {
        flag = 1;
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (m[n][i] && !p[m[n][i]]) {
            p[m[n][i]] = 1;
            dfs(m[n][i]);
            p[m[n][i]] = 0;
        }
    }
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (!n) break;
        flag = 0;
        for (int i = 1; i <= n; i++) p[i] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 3; j++) scanf("%d", &m[i][j]);
        }

        scanf("%d", &e);
        p[1] = 1;
        dfs(1);
        printf("%s\n", flag ? "YES" : "NO");
    }
}
