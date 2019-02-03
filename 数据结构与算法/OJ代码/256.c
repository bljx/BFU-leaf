// http://www.bjfuacm.com/problem/256/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1000

int main() {
    char* a;
    char* b;
    int flag;
    while (1) {
        flag = 0;
        a = (char *)calloc(LEN, sizeof(char));
        b = (char *)calloc(LEN, sizeof(char));
        scanf("%s %s", b, a);
        if (a[0] == '0' && b[0] == '0') break;
        int len_a = (int)strlen(a);
        int len_b = (int)strlen(b);

        for (int i = len_b; i < 2 * len_b; i++) {
            b[i] = b[i - len_b];
        }
        for (int i = 0; i < len_a - len_b + 1; i++) {
            for (int j = 0; j < len_b; j++) {
                int ck = 1; // default match
                for (int k = 0; k < len_b; k++) {
                    if (a[i + k] != b[j + k]) ck = 0;
                }
                if (ck) {
                    flag = 1;
                    break;
                }
            }
        }
        printf("%s\n", flag ? "YES" : "NO");

        free(a);
        free(b);
    }
}

/*******
 * KMP *
 *******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LEN 1000

int* compute(int* lps, char* pat) {
    int N = strlen(pat);
    lps = (int *)calloc(N, sizeof(int));
    lps[0] = 0;
    int index = 0;
    for (int i = 1; i < N; ) {
        if (pat[index] == pat[i]) {
            lps[i] = index + 1;
            index += 1;
            i += 1;
        } else {
            if (index != 0) {
                index = lps[index - 1];
            } else {
                lps[i] = 0;
                i += 1;
            }
        }
    }
    return lps;
}

bool KMP(char* txt, char* pat) {
    int* lps = compute(lps, pat);
    // lps refers to "the longest proper prefix which is also suffix"
    int i = 0;
    int j = 0;
    while (i < strlen(txt) && j < strlen(pat)) {
        if (txt[i] == pat[j]) {
            i += 1;
            j += 1;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i += 1;
            }
        }
    }
    free(lps);
    return j == strlen(pat);
}



int main() {
    char* pat;
    char* txt;
    bool flag;
    while (1) {
        flag = 0;
        pat = (char *)calloc(LEN, sizeof(char));
        txt = (char *)calloc(LEN, sizeof(char));

        scanf("%s %s", pat, txt);
        if (pat[0] == '0' && txt[0] == '0') break;
        int len_pat = strlen(pat);
        int len_txt = strlen(txt);

        for (int i = len_pat; i < 2 * len_pat; i++) {
            // do loop pat
            flag = KMP(txt, pat + i - len_pat) ? 1 : 0;
            if (flag) break;
            pat[i] = pat[i - len_pat];
        }
        free(pat);
        free(txt);
        printf("%s\n", flag ? "YES" : "NO");

    }
}