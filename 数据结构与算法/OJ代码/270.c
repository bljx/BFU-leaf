// http://www.bjfuacm.com/problem/270/

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
void CountGrade(SearchTree , int * , int * , int * );
void MakeEmpty(SearchTree );


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
        int hoge = 0, piyo = 0, fuga = 0;
        CountGrade(root, &hoge, &piyo, &fuga);
        printf("%d %d %d\n", hoge, piyo, fuga);
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

void CountGrade(SearchTree p, int *a, int *b, int *c)
{
    if (p == NULL) return;
    CountGrade(p->left, a, b, c);
    CountGrade(p->right, a, b, c);
    if (p->left == NULL && p->right == NULL) {
        (*a)++;
    } else if (p->left == NULL || p->right == NULL) {
        (*b)++;
    } else {
        (*c)++;
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
