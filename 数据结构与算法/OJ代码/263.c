// http://www.bjfuacm.com/problem/263/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
bool isSameTree(SearchTree , SearchTree );
void MakeEmpty(SearchTree );


int main()
{
    char *in;
    char *str1;
    char *str2;
    Position root1;
    Position root2;
    while (1) {
        in = (char *)calloc(LEN, sizeof(*in));
        scanf("%s", in);
        if ((*in) == '0' && (*(in + 1)) == '\0') break;
        str1 = in;
        root1 = BuildBT(&str1);
        memset(in, '\0', sizeof(*in) * LEN);
        scanf("%s", in);
        str2 = in;
        root2 = BuildBT(&str2);
        printf("%s\n", isSameTree(root1, root2)? "YES": "NO");
        MakeEmpty(root1);
        MakeEmpty(root2);
        free(in);
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

bool isSameTree(SearchTree p, SearchTree q)
{
    if (p != NULL &&  q != NULL) {
        if (p->Element != q->Element) return false;
        if (!isSameTree(p->left, q->left)) return false;
        if (!isSameTree(p->right, q->right)) return false;
    } else {
        return p == q;
    }
    return true; // in case "Control may reach end of non-void function" (Xcode)
}

void MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}
