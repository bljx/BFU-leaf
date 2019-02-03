// http://www.bjfuacm.com/problem/284/

#include <stdio.h>
#include <stdlib.h>

#define MVNum 100

struct ArcNode;
struct VNode;
struct ALGragh;
typedef struct ArcNode ArcNode;
typedef struct VNode VNode;
typedef struct ALGragh ALGragh;

typedef char VerTexType;
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
int DFS(ALGragh * , int , int , int * , int * );
void DestroyALGraph(ALGragh * );
void DestroyArcList(ArcNode * );


int main()
{
    VerTexType vex;
    VerTexType v1;
    VerTexType v2;
    int level;

    while (1) {
        ALGragh *G = (ALGragh *)calloc(1, sizeof(*G));
        G = CreateUDG(G);
        if (G == NULL) break;
        // use array to label visited here

        int *vis = (int *)calloc(G->vexnum + 1, sizeof(int));
        scanf("%c%c", &v1, &v2);
        getchar();
        level = 1;

        int ans = DFS(G, LocateVex(G, v1), LocateVex(G, v2), &level, vis);
        printf("%s\n", ans == 1? "YES": "NO");

        DestroyALGraph(G);
        free(vis);
    }
}

ALGragh * CreateUDG(ALGragh *G)
{
    VerTexType v1; // node 1, is a name
    VerTexType v2; // node 2, is also a name

    scanf("%d %d", &(G->vexnum), &(G->arcnum));
    if (G->vexnum == 0 && G->arcnum == 0) return NULL;
    getchar();
    for (int i = 1; i <= G->vexnum; i++) {
        scanf("%c", &(G->vertices[i].data));
    }
    getchar();
    for (int k = 1; k <= G->arcnum; k++) {
        scanf("%c%c", &v1, &v2);
        getchar();

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

int DFS(ALGragh *G, int i, int j, int *level, int *vis)
{
    if (i == j) return 1;

    else {
        vis[i] = 1;
        for (ArcNode *p = G->vertices[i].firstarc; p; p = p->nextarc, (*level)--) {
            (*level)++;
            int k = p->adjvex;
            if (!vis[k] && DFS(G, k, j, level, vis)) {
                return 1;
            }
        }

        if (level == 1) return 0;
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
