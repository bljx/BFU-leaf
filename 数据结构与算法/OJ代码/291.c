// http://www.bjfuacm.com/problem/291/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LEN 1000

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;

struct TreeNode {
    ElementType Element;
    SearchTree left;
    SearchTree right;
};

Position BuildBT(char ** );
void MakeEmpty(SearchTree );
int Height(SearchTree );


int main()
{
    char *in = (char *)calloc(LEN, sizeof(char));
    char *str;
    Position root;
    while (1) {
        memset(in, '\0', LEN * sizeof(char));
        scanf("%s", in);
        if ((*in) == '#' && (*(in + 1)) == '\0') break;
        str = in;
        root = BuildBT(&str);
        printf("%d\n", Height(root));
        MakeEmpty(root);
    }
}

Position BuildBT(char **in)
{
    if (**in == '#') return NULL;
    Position T = (Position)calloc(1, sizeof(*T));
    T->Element = **in;
    (*in)++;
    T->left = BuildBT(&(*in));
    (*in)++;
    T->right = BuildBT(&(*in));
    /**
     * in C taking address of ++(*in) which is a rvalue is illegal
     * thus we can't write BuildBT(&(++(*in)));
     * while in C++ it's compilable
     */
    return T;
}

void MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}

int Height(SearchTree p)
{
    if (p == NULL) return 0;
    int lHeight = Height(p->left);
    int rHeight = Height(p->right);
    return (lHeight > rHeight)? (lHeight + 1): (rHeight + 1);
}
