// http://www.bjfuacm.com/problem/275/

// typedef type array here:
// https://stackoverflow.com/questions/4523497/typedef-fixed-length-array

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
int LocateVex(ALGragh * , int );
ALGragh * AddVex(ALGragh * );
void PrintALGraph(ALGragh * );
void DestroyALGraph(ALGragh * );
void DestroyArcList(ArcNode * );


int main()
{
    while (1) {
        ALGragh *G = (ALGragh *)calloc(1, sizeof(*G));
        G = CreateUDG(G);
        if (G == NULL) break;
        G = AddVex(G);
        PrintALGraph(G);
        DestroyALGraph(G);
    }
}

ALGragh * CreateUDG(ALGragh *G)
{
    int v1; // node 1, is a name
    int v2; // node 2, is also a name

    scanf("%d %d", &(G->vexnum), &(G->arcnum));
    if (G->vexnum == 0 && G->vexnum == 0) return NULL;
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

int LocateVex(ALGragh * G, int idx)
{
    /**
     * brief: give name, which is an int (idx in this case), according to index
     * params: graph, vertex's index
     * retval: vertex's name
     */
    return G->vertices[idx].data;
}

ALGragh * AddVex(ALGragh * G)
{
    VerTexType data;
    scanf("%d", &data);
    G->vexnum = G->vexnum + 1;
    G->vertices[G->vexnum].data = data;
    G->vertices[G->vexnum].firstarc = NULL;
    return G;
}

void PrintALGraph(ALGragh * G)
{
    if (G == NULL) return;
    for (int i = 1; i <= G->vexnum; i++) {
        printf("%d%s", G->vertices[i].data, G->vertices[i].firstarc == NULL? "\n": " ");
        if (G->vertices[i].firstarc != NULL) {
            ArcNode *p = G->vertices[i].firstarc;
            while (p != NULL) {
                printf("%d%s", p->adjvex, p->nextarc == NULL? "\n": " ");
                p = p->nextarc;
            }
        }
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
