// http://www.bjfuacm.com/problem/298/

#include <stdio.h>

int Search(int r[], int low, int high, int key) {
    while (low < high) {
        while (r[low] > key && r[high] < key) {
            low++;
            high--;
        }
        while (low <= high && r[high] > key) high--;
        if (r[high] == key) return high;
        while (low <= high && r[low] < key) low++;
        if (r[low] == key) return low;
    }
    return -1;
}

int main()
{
    int arr[50];
    int num;
    while (scanf("%d", &num) && num != 0) {
        for (int i = 0; i < num; i++) {
            scanf("%d", &arr[i]);
        }
        int key;
        scanf("%d", &key);
        int ans = Search(arr, 0, num - 1, key);
        if (ans == -1) {
            printf("%s\n", "not find");
        } else {
            printf("%d %d\n", ans + 1, arr[ans]);
        }
    }
}