// www.bjfuacm.com/problem/283/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INT 32767
#define MVNum 100

typedef int VerTexType;
typedef int ArcType;

struct AMGraph;
typedef struct AMGraph AMGraph;

struct AMGraph {
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum;
    int arcnum;
};

int LocateVex(AMGraph * , VerTexType );
AMGraph * CreateUDN(AMGraph * );
void Dijkstra(AMGraph * , VerTexType );
int MinUnprocessedDistance(int * , bool * , int );
void DestroyGraph(AMGraph * );

int main()
{
    VerTexType a; // node
    while (1) {
        AMGraph *G = (AMGraph *)calloc(1, sizeof(*G));
        G = CreateUDN(G);
        if (G == NULL) break;
        scanf("%d", &a);
        Dijkstra(G, a);
        DestroyGraph(G);
    }
}

int LocateVex(AMGraph *G, VerTexType vex)
{
    for (int i = 1; i <= G->vexnum; i++) {
        if (vex == G->vexs[i]) return i;
    }
}


AMGraph * CreateUDN(AMGraph *G)
{
    VerTexType v1; // node 1, is a name
    VerTexType v2; // node 2, is also a name

    scanf("%d %d", &(G->vexnum), &(G->arcnum));
    if (G->vexnum == 0 && G->arcnum == 0) return NULL;

    for (int i = 1; i <= G->vexnum; i++) {
        G->vexs[i] = i;
    }
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = 1; j <= G->vexnum; j++) {
            G->arcs[i][j] = 0; // use "0" -> no connection here
            // thus we can use it as bool
        }
    }

    
    int i; // index of arch_1
    int j; // index of arch_2
    int weight;
    for (int k = 1; k <= G->arcnum; k++) {
        scanf("%d %d %d", &v1, &v2, &weight);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
    }
    return G;
}

int MinUnprocessedDistance(int *dist, bool *sptSet, int v)
{
    int min = INT_MAX;
    int idx;

    for (int i = 1; i <= v; i++) {
        if (sptSet[i] == false && dist[i] <= min) {
            min = dist[i];
            idx = i;
        }
    }

    return idx;
}

void Dijkstra(AMGraph *G, VerTexType a)
{
    int idx = LocateVex(G, a); // i is source
    // should int only when count

    int v = G->vexnum; // node amount

    int dist[v + 1]; // start from 1
    int parent[v + 1]; // record shortest path tree
    bool sptSet[v + 1]; // true if vertex in "shortest path tree"

    for (int i = 1; i <= v; i++) {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[idx] = 0; // source node is always 0

    for (int i = 1; i <= v; i++) {
        // here "i" is a counter
        // "while" is also acceptable
        int u = MinUnprocessedDistance(dist, sptSet, v);
        sptSet[u] = true;

        for (int j = 1; j <= v; j++) {
            /**
             * condition:
             * 1. node is unprocessed !sptSet[j]
             * 2. edge exists G->arcs[u][j] is not "0"
             * 3. weight of src->u->v < src->v
             */
            if (!sptSet[j] && G->arcs[u][j] && dist[u] + G->arcs[u][j] < dist[j]) {
                parent[j] = u;
                dist[j] = dist[u] + G->arcs[u][j];
            }
        }
    }

    int dis = INT_MIN;
    int index = 1;

    for (int i = 1; i <= v; i++) {
        if (dist[i] != INT_MAX && dis <dist[i]) {
            index = i;
            dis = dist[i];
        }
    }

    printf("%d\n", index);
    printf("%d\n", dis);


}

void DestroyGraph(AMGraph *G)
{
    free(G);
}
