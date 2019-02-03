// http://www.bjfuacm.com/problem/268/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1000

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef char ElementType;

struct TreeNode {
    ElementType Element;
    SearchTree left;
    SearchTree right;
};

Position BuildBT(char ** );
void PathTraversal(SearchTree , ElementType * , int );
void MakeEmpty(SearchTree );


int main()
{
    char *in = (char *)calloc(LEN, sizeof(char));
    char *path = (char *)calloc(LEN, sizeof(char));
    char *str;
    Position root;
    while (1) {
        memset(in, '\0', LEN * sizeof(char));
        memset(path, '\0', LEN * sizeof(char));
        scanf("%s", in);
        if ((*in) == '0' && (*(in + 1)) == '\0') break;
        str = in;
        root = BuildBT(&str);
        PathTraversal(root, path, 0);
        MakeEmpty(root);
    }
}

Position BuildBT(char **in)
{
    if (**in == '0') return NULL;
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

void PathTraversal(SearchTree T, ElementType *path, int len)
{
    if (T == NULL) return;
    if (T->left == NULL && T->right == NULL) {
        printf("%c", T->Element);
        for (int i = len - 1; i >= 0; i--) {
            printf("%c", path[i]);
        }
        printf("%s", "\n");
    } else {
        path[len++] = T->Element;
        PathTraversal(T->left, path, len);
        PathTraversal(T->right, path, len);
    }
}

void MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}
