// http://www.bjfuacm.com/problem/282/

#include <stdio.h>
#include <stdlib.h>

#define MVNum 100

struct ArcNode;
struct VNode;
struct ALGragh;
typedef struct ArcNode ArcNode;
typedef struct VNode VNode;
typedef struct ALGragh ALGragh;

typedef int VerTexType;
typedef int ArcType;

struct ArcNode {
    int adjvex;
    ArcNode *nextarc;
};

struct VNode {
    VerTexType data;
    ArcNode *firstarc;
};

typedef struct VNode AdjList[MVNum];
/**
 * ALGraph need AdjList declare first
 * typedef array need complete element type 'struct VNode'
 */

struct ALGragh {
    AdjList vertices; // vertices is pl. of vertex (index, indices)
    int vexnum;
    int arcnum;
};

ALGragh * CreateUDG(ALGragh * );
int LocateVex(ALGragh * , VerTexType );
void DFS(ALGragh * , int , int * );
void DestroyALGraph(ALGragh * );
void DestroyArcList(ArcNode * );


int main()
{
    VerTexType vex;
    while (1) {
        ALGragh *G = (ALGragh *)calloc(1, sizeof(*G));
        G = CreateUDG(G);
        if (G == NULL) break;
        scanf("%d", &vex);

        // use array to label visited here
        int *vis = (int *)calloc(G->vexnum + 1, sizeof(int));

        DFS(G, LocateVex(G, vex), vis);
        DestroyALGraph(G);
        free(vis);
    }
}

ALGragh * CreateUDG(ALGragh *G)
{
    int v1; // node 1, is a name
    int v2; // node 2, is also a name

    scanf("%d %d", &(G->vexnum), &(G->arcnum));
    if (G->vexnum == 0 && G->arcnum == 0) return NULL;
    for (int i = 1; i <= G->vexnum; i++) {
        // since G is a pointer, use "->"
        G->vertices[i].data = i; // data refers to "ith" (type: int) node
        G->vertices[i].firstarc = NULL; // head node
    }
    for (int k = 1; k <= G->arcnum; k++) {
        scanf("%d %d", &v1, &v2);
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        ArcNode *p = (ArcNode *)calloc(1, sizeof(*p)); // new node
        p->adjvex = j;
        p->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = p;

        ArcNode *q = (ArcNode *)calloc(1, sizeof(*q)); // new node otherside
        q->adjvex = i;
        q->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = q;
    }
    return G;
}

void DFS(ALGragh *G, int idx, int *vis)
{
    /**
     * brief: DFS recursive (reach end) at :
     * 1. firstarc == NULL;
     * 2. p->nextarc == NULL;
     * thus assign two ptr is complex, use iterative
     */

    int stack[200];
    int cnt = 0;
    int e;
    int num = 0;
    ArcNode *p;

    stack[cnt++] = idx;
    while (cnt != 0) {
        e = stack[--cnt];
        if (!vis[e]) {
            // method: push each ArchNode to the stack
            printf("%d%s", e, (++num) == G->vexnum? "\n": " ");
            vis[e] = 1;
            p = G->vertices[e].firstarc;
            while (p != NULL) {
                if (!vis[p->adjvex]) {
                    stack[cnt++] = p->adjvex;
                }
                p = p->nextarc;
            }
        }
    }
}

int LocateVex(ALGragh * G, VerTexType vex)
{
    /**
     * return idx according to vex'name
     */
    for (int i = 1; i <= G->vexnum; i++) {
        if (G->vertices[i].data == vex) return i;
    }
}

void DestroyALGraph(ALGragh *G)
{
    if (G == NULL) return;
    for (int i = 1; i <= G->vexnum; i++) {
        if (G->vertices[i].firstarc != NULL) {
            DestroyArcList(G->vertices[i].firstarc);
        }
    }
    free(G);
}

void DestroyArcList(ArcNode *p)
{
    ArcNode *to_delete = NULL;
    while (p != NULL) {
        to_delete = p;
        p = p->nextarc;
        free(to_delete);
    }
}
