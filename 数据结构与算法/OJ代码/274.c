// http://www.bjfuacm.com/problem/274/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 17234

int bfs(int i, int N, int **g) {
    /**
     * brief: breadth first search graph
     * params: ith node to count, node amount and graph
     * retval: node amount in graph which reaches 6 level
     */
    int queue[MAXN];
    int vis[MAXN];
    int front;
    int rear;
    int count;
    int level;
    int last; // last level's last node
    int tail; // cur level's last node
    int cur; // current node

    memset(vis, 0, sizeof(vis));
    vis[i] = 1;
    front = rear = -1;
    count = 1;
    level = 0;
    last = i;
    queue[++rear] = i;

    while (front < rear) { // similar to BST level order traversal
        cur = queue[++front];
        for (int j = 1; j <= N; j++) {
            if (!vis[j] && g[cur][j] == 1) {
                /**
                 * condition:
                 * 1. this node is not visited
                 * 2. path from cur to this node exists
                 */
                queue[++rear] = j;
                vis[j] = 1; // mark this is visited
                count++;
                tail = j; // tail can be cur level's last node
            }
        }

        if (cur == last) {
            level++;
            last = tail;
        }
        if (level == 6) {
            break;
        }
    }

    return count;
}

void destroy(int **g, int N) {
    for (int i = 0; i <= N; i++) {
        free(g[i]);
        g[i] = NULL;
    }
    free(g);
}

int main() {
    int N, M;
    int count;
    int **g; // adjacent graph
    int x; // coordinate x axis
    int y; // coordinate y axis
    
    while (1) {
        scanf("%d %d", &N, &M);
        if (N == 0 && M == 0) break;
        g = (int **)calloc(N + 1, sizeof(int *));
        if (g == NULL) exit(14);

        for (int i = 0; i <= N; i++) {
            g[i] = (int *)calloc(N + 1, sizeof(int));
            if (g[i] == NULL) exit(14);
        }

        for (int i = 0; i < M; i++) {
            scanf("%d %d", &x, &y);
            g[x][y] = 1;
            g[y][x] = 1;
        }

        for (int i = 1; i <= N; i++) {
            count = bfs(i, N, g);
            printf("%d: %.2f%%\n", i, (float)count / N * 100);
        }

        destroy(g, N);
    }
}