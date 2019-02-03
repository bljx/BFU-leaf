// http://www.bjfuacm.com/problem/267/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void LongestPath(SearchTree , ElementType * , int , bool * , int );
int Height(SearchTree );
void MakeEmpty(SearchTree );


int main()
{
    char *in = (char *)calloc(LEN, sizeof(char));
    char *path = (char *)calloc(LEN, sizeof(char));
    char *str;
    Position root;
    bool first;
    while (1) {
        memset(in, '\0', LEN * sizeof(char));
        memset(path, '\0', LEN * sizeof(char));
        first = true;
        scanf("%s", in);
        if ((*in) == '0' && (*(in + 1)) == '\0') break;
        str = in;
        root = BuildBT(&str);
        printf("%d\n", Height(root));
        LongestPath(root, path, 0, &first, Height(root));
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

void LongestPath(SearchTree T, ElementType *path, int len, bool *first, int height)
{
    if (T == NULL) return;
    if (T->left == NULL && T->right == NULL) {
        if (*first && len + 1 == height) {
            for (int i = 0; i < len; i++) {
                printf("%c", path[i]);
            }
            printf("%c", T->Element);
            printf("%s", "\n");
            *first = false;
        }
    } else {
        path[len++] = T->Element;
        LongestPath(T->left, path, len, first, height);
        LongestPath(T->right, path, len, first, height);
    }
}

int Height(SearchTree p)
{
    if (p == NULL) return 0;
    int lHeight = Height(p->left);
    int rHeight = Height(p->right);
    return (lHeight > rHeight)? (lHeight + 1): (rHeight + 1);
}

void MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}
