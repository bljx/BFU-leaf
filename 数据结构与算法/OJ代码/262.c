// http://www.bjfuacm.com/problem/262/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXLEN 1000

typedef struct {
    // n nodes for 2 * n - 1 HTNodes
    int weight;
    int parent, lchild, rchild; // record pos of related nodes
    char ch;
    char* encode;
    bool unused; // false if it is visited
} HTNode, *HuffmanTree;

typedef struct {
    // n nodes for n HCNodes
    char* code; // record encode of characters
    char ch;
} HCNode, *HuffmanCode;

int** CreateAlpha(char* );
void PrintFrequency(int* , int );
HuffmanTree CreateHuffmanTree(const int* , int );
int FindMinWeightIndex(HuffmanTree , int );
HuffmanCode* GetHuffmanCode(HuffmanTree , int );
void PrintHuffmanTreeTable(HuffmanTree , int );
HuffmanCode* sort(HuffmanCode* , int );
void PrintEncode(HuffmanCode* , HuffmanTree , int );


int main()
{
    char* in; // input array
    while (1) {
        in = (char *)calloc(MAXLEN, sizeof(char));
        scanf("%s", in);
        if ((*in) == '0' && (*(in + 1)) == '\0') break;
        int** ptr = CreateAlpha(in);
        int n = *(ptr[0]);
        int* alpha = ptr[1];
        // second way: use two int* one for num another for index (char)
        
        PrintFrequency(alpha, n);
        HuffmanTree HT = CreateHuffmanTree(alpha, n);
        PrintHuffmanTreeTable(HT, n * 2 - 1);
        HuffmanCode *codes = GetHuffmanCode(HT, n);
        codes = sort(codes, n);
        PrintEncode(codes, HT, n);
        printf("%s\n", in);

        free(ptr[1]); // alphabet
        free(ptr[0]);
        free(HT); // free table created during building
        free(*codes); // free set of encode struct
    }
}

int** CreateAlpha(char* str)
{
    /**
     * brief: create a alphabet and count
     * params: input string
     * retval: a pointer contain valid size and alpha table
     */
    size_t LEN = strlen(str);
    int* alpha = (int *)calloc(26, sizeof(int)); // a ~ z: 97 ~ 122
    int* size = (int *)malloc(sizeof(int));
    (*size) = 0;
    for (size_t i = 0; i < LEN; i++) {
        alpha[str[i] - 97] += 1;
        if (alpha[str[i] - 97] == 1) (*size)++;
    }
    int** ptr = (int **)calloc(2, sizeof(int*));
    ptr[0] = size;
    ptr[1] = alpha;
    return ptr;
}

void PrintFrequency(int* alpha, int n)
{
    /**
     * brief: print frequency of input string
     * params: dict and valid size
     */
    for (int i = 0; i < 26; i++) {
        if (alpha[i] > 0) {
            n--;
            printf("%c:%d%s", 97 + i, alpha[i], n == 0 ? "\n" : " ");
        }
    }
}

HuffmanTree CreateHuffmanTree(const int* dict, int n)
{
    /**
     * brief: create a huffman tree
     * params: alphabet and valid size
     * retval: a huffman tree according to the dict
     */
    int m = 2 * n - 1; // all nodes: n = 2 * n0 - 1
    HuffmanTree HT = (HTNode *)malloc((m + 1) * sizeof(*HT)); // leap idx = 0
    for (int i = 1; i <= m; i++) {
        // since HT is a pointer
        // HT[i] equals to *(HT + i) which is a HTNode variable
        // as it calls its member using '.', HT[i].member
        // which is equivalent to (*(HT + i)).member and (HT + i)->member
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].unused = true;
        // this loop can be omitted if we use `calloc`
    }
    int HT_idx = 1;
    for (int i = 0; i < 26; i++) {
        // use alphabet to initialize
        if (dict[i] > 0) {
            HT[HT_idx].ch = (char)(97 + i);
            HT[HT_idx].weight = dict[i];
            HT_idx++;
        }
    }
    /** huffman tree initialized */
    /** huffman tree building */
    int s1, s2;
    for (int i = n + 1; i <= m; i++) {
        // search here priority queue is preferred, but we do not use
        s1 = FindMinWeightIndex(HT, i - 1);
        s2 = FindMinWeightIndex(HT, i - 1);
        // since get s1 first, HT[s1].weight < HT[s2].weight, do like BST
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    return HT;
}

int FindMinWeightIndex(HuffmanTree HT, int num)
{
    /**
     * brief: search for index of minimum unused weight, mark it as used
     * params: huffman tree and range of possible weight
     * retval: index (start from 1) of minimum unused weight
     */
    int min = INT_MAX; // INT_MAX is in "limits.h"
    int index = -1;
    for (int i = 1; i <= num; i++) {
        if (HT[i].unused && min > HT[i].weight) {
            min = HT[i].weight;
            index = i;
        }
    }
    HT[index].unused = false;
    return index;
}

HuffmanCode* GetHuffmanCode(HuffmanTree HT, int n)
{
    /**
     * brief: retrieve encode for every characters
     * params: huffman tree and amount of character
     * retval: a pointer to pointers of HCNode that contains encode
     */
    HuffmanCode* codes = (HCNode **)calloc(n + 1, sizeof(*codes)); // leave codes[0] empty
    char* ch = (char *)calloc(n, sizeof(*ch)); // temporary char* for each HCNode
    int start; // encode string from index = n - 1
    int cur; // index of HT
    int f; // index of HT (parent)
    for (int i = 1; i <= n; i++) {
        // loop HT
        start = n - 1;
        cur = i;
        f = HT[i].parent;
        codes[i] = (HCNode *)calloc(1, sizeof(HCNode));
        (*(codes[i])).ch = HT[i].ch;
        while (f != 0) {
            --start;
            if (HT[f].lchild == cur) {
                ch[start] = '0';
            } else {
                // HT[f].rchild == cur
                ch[start] = '1';
            }
            cur = f;
            f = HT[f].parent;
        }
        (*(codes[i])).code = (char *)calloc(n - start, sizeof(char));
        HT[i].encode = (char *)calloc(n - start, sizeof(char));
        strcpy((*(codes[i])).code, &ch[start]);
        strcpy(HT[i].encode, &ch[start]);
    }
    free(ch);
    return codes;
}

void PrintHuffmanTreeTable(HuffmanTree HT, int n)
{
    /**
     * brief: print table of building huffman tree
     * params: HT and number of nodes (2 * n0  - 1)
     */
    for (int i = 1; i <= n; i++) {
        printf("%d %d %d %d %d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    }
}

HuffmanCode* sort(HuffmanCode* codes, int n)
{
    /**
     * brief: insertion sort pointers by ASCII
     * params: pointer to pointers to HCNode and valid size
     * retval: a new pointer contains ASCII order of pointers
     */
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if ((codes[i])->ch > (codes[j])->ch) {
                HuffmanCode temp = codes[i];
                codes[i] = codes[j];
                codes[j] = temp;
            }
        }
    }
    return codes;
}

void PrintEncode(HuffmanCode* codes, HuffmanTree HT, int n)
{
    /**
     * brief: print codes for every characters, print encode string
     * params: pointer of pointers of *HuffmanCode, HT and valid size
     */
    for (int i = 1; i <= n; i++) {
        printf("%c:%s%s", (codes[i])->ch, (codes[i])->code, i == n ? "\n" : " ");
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < HT[i].weight; j++) {
            printf("%s", HT[i].encode);
        }
    }
    printf("\n");
}
