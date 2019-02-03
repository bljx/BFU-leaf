// http://www.bjfuacm.com/problem/276/

#include <stdio.h>
#include <stdlib.h>

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
void AddVex(AMGraph * );
void PrintGraph(AMGraph * );
void DestroyGraph(AMGraph * );

int main()
{
    while (1) {
        AMGraph *G = (AMGraph *)calloc(1, sizeof(*G));
        G = CreateUDN(G);
        if (G == NULL) break;
        AddVex(G);
        PrintGraph(G);
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
    int v1; // node 1, is a name
    int v2; // node 2, is also a name

    scanf("%d %d", &(G->vexnum), &(G->arcnum));
    if (G->vexnum == 0 && G->vexnum == 0) return NULL;
    for (int i = 1; i <= G->vexnum; i++) {
        G->vexs[i] = i;
    }
    for (int i = 1; i <= G->vexnum; i++) {
        for (int j = 1; j <= G->vexnum; j++) {
            G->arcs[i][j] = 0; // no connection here
        }
    }

    int i; // index of arch_1
    int j; // index of arch_2
    for (int k = 1; k <= G->arcnum; k++) {
        scanf("%d %d", &v1, &v2);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G->arcs[i][j] = 1;
        G->arcs[j][i] = 1;
    }
    return G;
}

void AddVex(AMGraph *G)
{
    VerTexType vex;
    scanf("%d", &vex);
    G->vexnum = G->vexnum + 1;
    // TODO: init and enclose the graph
    // since we calloc G, leap this

    G->vexs[G->vexnum] = vex;
}


void PrintGraph(AMGraph *G)
{
    for (int i = 0; i <= G->vexnum; i++) {
        printf("%d%s", G->vexs[i], i == G->vexnum? "\n": " ");
    }
    for (int i = 1; i <= G->vexnum; i++) {
        printf("%d ", G->vexs[i]);
        for (int j = 1; j <= G->vexnum; j++) {
            printf("%d%s", G->arcs[i][j], j == G->vexnum? "\n": " ");
        }
    }
}

void DestroyGraph(AMGraph *G)
{
    free(G);
}
