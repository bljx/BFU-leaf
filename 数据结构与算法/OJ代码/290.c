// http://www.bjfuacm.com/problem/290/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode;
struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    int val;
    int count;
};

typedef struct TreeNode *PtrToTree;
typedef PtrToTree SearchTree;

SearchTree BuildBST(int );
void PrintTree(SearchTree , int );
void DestroyTree(SearchTree );
int GetMax(SearchTree );
void InsertNode(SearchTree , SearchTree , SearchTree , SearchTree );
void PrintCount(SearchTree , int );

int main()
{
    int n; // node num
    int m; // search node

    while (1) {

        scanf("%d", &n);
        if (n == 0) break;
        SearchTree K = BuildBST(n);
        scanf("%d", &m);

        SearchTree i = (SearchTree)calloc(1, sizeof(*i));
        i->val = m;
        SearchTree pre;
        SearchTree q;
        InsertNode(pre, q, i, K);

        PrintTree(K, GetMax(K));
        PrintCount(K, GetMax(K));
        DestroyTree(K);
    }

}

void InsertNode(SearchTree pre, SearchTree q, SearchTree p, SearchTree root)
{
    /**
     * params:
     * pre (q'previous) to assign ptr
     * q to get right pos
     * p is node to insert
     * root node
     */

    q = root;
    while (q != NULL) {
        if (p->val > q->val) {// go right
            pre = q;
            q = q->right;
        } else if (p->val < q->val) {
            pre = q;
            q = q->left;
        } else { // p->val == q->val
            q->count += 1;
            free(p);
            return;
        }
    }
    if (p->val > pre->val) {
        pre->right = p;
    } else { // p->val < pre
        pre->left = p;
    }

}

SearchTree BuildBST(int n)
{
    SearchTree p;
    SearchTree root;
    SearchTree q; // get right position
    SearchTree q_p; // save q's previous to assign pointer

    for (int i = 0; i < n; i++) {
        p = (SearchTree)calloc(1, sizeof(*p));
        scanf("%d", &(p->val));
        p->left = NULL;
        p->right = NULL;
        p->count = 0;
        if (i == 0) { // is root
            root = p;
        } else {
            InsertNode(q_p, q, p, root);
        }
    }
    return root;
}

int GetMax(SearchTree K)
{
    if (K->right != NULL) {
        return GetMax(K->right);
    } else {
        return K->val;
    }
}

void PrintTree(SearchTree K, int max)
{
    if (K == NULL) return;
    PrintTree(K->left, max);
    printf("%d%s", K->val, K->val == max? "\n": " ");
    PrintTree(K->right, max);
}

void PrintCount(SearchTree K, int max)
{
    if (K == NULL) return;
    PrintCount(K->left, max);
    printf("%d%s", K->count, K->val == max? "\n": " ");
    PrintCount(K->right, max);
}

void DestroyTree(SearchTree K)
{
    if (K == NULL) return;
    DestroyTree(K->left);
    DestroyTree(K->right);
    free(K);
}
