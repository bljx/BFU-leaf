// http://www.bjfuacm.com/problem/257/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000

/**************
 *   ASCII:   *
 * A-Z: 65-90 *
 * 0-9: 48-57 *
 **************/

int main() {
    char* a;
    int dict[91];

    while (1) {
        a = (char *)calloc(MAXN, sizeof(char));
        memset(dict, 0, 91 * sizeof(int));
        scanf("%s", a);
        if (a[0] == '0' && a[1] == '\0') break;
        int len = (int)strlen(a);
        for (int i = 0; i < len; i++) {
            dict[(int)a[i]] += 1;
        }
        for (int i = 48; i <= 57; i++) {
            if (dict[i] > 0) printf("%c:%d\n", (char)i, dict[i]);
        }
        for (int i = 65; i <= 90; i++) {
            if (dict[i] > 0) printf("%c:%d\n", (char)i, dict[i]);
        }
        free(a);
    }
}

// REF: https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c