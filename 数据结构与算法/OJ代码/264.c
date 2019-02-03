// http://www.bjfuacm.com/problem/264/

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
void MakeEmpty(SearchTree );
void SwapChildren(SearchTree );
void PreorderTraversal(SearchTree );


int main()
{
    char *in = (char *)calloc(LEN, sizeof(char));
    char *str;
    Position root;
    while (1) {
        memset(in, '\0', LEN * sizeof(char));
        scanf("%s", in);
        if ((*in) == '0' && (*(in + 1)) == '\0') break;
        str = in;
        root = BuildBT(&str);
        SwapChildren(root);
        PreorderTraversal(root);
        printf("\n");
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

void SwapChildren(SearchTree p)
{
    if (p == NULL) return;
    SwapChildren(p->left);
    SwapChildren(p->right);
    Position temp = p->right;
    p->right = p->left;
    p->left = temp;
}

void PreorderTraversal(SearchTree p)
{
    if (p == NULL) return;
    printf("%c", p->Element);
    PreorderTraversal(p->left);
    PreorderTraversal(p->right);
}

void MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}
