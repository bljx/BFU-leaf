// www.bjfuacm.com/problem/273/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INT 32767
#define MVNum 100

typedef char VerTexType;
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
int Dijkstra(AMGraph * , char , char );
int MinUnprocessedDistance(int * , bool * , int );
void Path(AMGraph * , int * , int , bool , int);
void DestroyGraph(AMGraph * );

int main()
{
    VerTexType a; // node 1
    VerTexType b; // node 2
    while (1) {
        AMGraph *G = (AMGraph *)calloc(1, sizeof(*G));
        G = CreateUDN(G);
        if (G == NULL) break;
        scanf("%c %c", &a, &b);
        Dijkstra(G, a, b);
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

    scanf("%d %d\n", &(G->vexnum), &(G->arcnum));
    if (G->vexnum == 0 && G->arcnum == 0) return NULL;

    for (int i = 1; i <= G->vexnum; i++) {
        scanf("%s", &(G->vexs[i])); // use "%s" to escape " " space
    }
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = 1; j <= G->vexnum; j++) {
            G->arcs[i][j] = 0; // use "0" -> no connection here
            // thus we can use it as bool
        }
    }


    getchar();

    int i; // index of arch_1
    int j; // index of arch_2
    int weight;
    for (int k = 1; k <= G->arcnum; k++) {
        scanf("%c %c %d\n", &v1, &v2, &weight);
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

int Dijkstra(AMGraph *G, VerTexType a, VerTexType b)
{
    int i = LocateVex(G, a); // i is source
    int aim = LocateVex(G, b); // locate a, b in vexs[].
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

    dist[i] = 0; // source node is always 0

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

    printf("%d\n", dist[aim]);
    Path(G, parent, aim, true, i);
}

void Path(AMGraph *G, int *parent, int aim, bool last, int src)
{
    if (parent[aim] == -1) {
        printf("%c ", G->vexs[src]);
        return;
    }
    Path(G, parent, parent[aim], false, src);
    printf("%c%s", G->vexs[aim], last == true? "\n": " ");

}

void DestroyGraph(AMGraph *G)
{
    free(G);
}
