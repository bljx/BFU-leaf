// http://www.bjfuacm.com/problem/289/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct TreeNode;
struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    int val;
};

typedef struct TreeNode *PtrToTree;
typedef PtrToTree SearchTree;

SearchTree BuildBST(int );
void PrintTree(SearchTree , int , int );
void DestroyTree(SearchTree );
int GetMax(SearchTree );

int main()
{
    int n; // node num
    int m; // search node

    while (1) {

        scanf("%d", &n);
        if (n == 0) break;
        SearchTree K = BuildBST(n);
        scanf("%d", &m);
        PrintTree(K, m, GetMax(K));
        DestroyTree(K);
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
        if (i == 0) { // is root
            root = p;
        } else {
            q = root;
            while (q != NULL) {
                if (p->val > q->val) {// go right
                    q_p = q;
                    q = q->right;
                } else { // p->val < q->val go left
                    q_p = q;
                    q = q->left;
                }
            }
            if (p->val > q_p->val) {
                q_p->right = p;
            } else { // p->val < q_p
                q_p->left = p;
            }
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

void PrintTree(SearchTree K, int m, int max)
{
    // Inorder traversal to get from small to large, and print conditionally
    if (K == NULL) return;
    PrintTree(K->left, m, max);
    if (K->val >= m) {
        printf("%d%s", K->val, K->val == max? "\n": " ");
    }
    PrintTree(K->right, m, max);
}

void DestroyTree(SearchTree K)
{
    if (K == NULL) return;
    DestroyTree(K->left);
    DestroyTree(K->right);
    free(K);
}
