// http://www.bjfuacm.com/problem/288/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

Position BuildTree(char ** );
bool dfs(SearchTree , int , int );
bool IsBST(SearchTree );
void MakeEmpty(SearchTree );

int main()
{
    char *in = (char *)calloc(LEN, sizeof(char));
    char *str;
    SearchTree root;
    while (1) {
        memset(in, '\0', LEN * sizeof(char));
        scanf("%s", in);
        if ((*in) == '#' && (*(in + 1)) == '\0') break;
        str = in;
        root = BuildTree(&str);
        printf("%s\n", IsBST(root)? "YES": "NO");
        MakeEmpty(root);
    }
}

Position BuildTree(char **in)
{
    if (**in == '#') return NULL;
    Position T = (Position)calloc(1, sizeof(*T));
    T->Element = **in;
    (*in)++;
    T->left = BuildTree(&(*in));
    (*in)++;
    T->right = BuildTree(&(*in));
    return T;
}

bool dfs(SearchTree p, int min, int max)
{
    if (p == NULL) return true;
    if (p->Element < min || p->Element > max) return false;
    if (p->left != NULL && p->Element == 97) return false;
    if (p->right != NULL && p->Element == 122) return false;
    return dfs(p->left, min, p->Element - 1) && dfs(p->right, p->Element + 1, max);
}

bool IsBST(SearchTree root)
{
    /**
     * a ~ z: 97 ~ 122
     */
    return dfs(root, 97, 122);
}

void MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}