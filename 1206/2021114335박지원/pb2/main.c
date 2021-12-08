#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) t=x;x=y;y=t

typedef struct {
    int key;
    char data[100];
}element;

void printarr(element arr[], int n) {
    for (int i = 1;i <= n;i++) {
        printf("%5s:%4d\n", arr[i].data, arr[i].key);
    }
    printf("\n");
}

void adjust(element a[], int root, int n) {
    element temp = a[root];
    int rootkey = a[root].key;
    printf("rootkey: %d\n", rootkey);
    int child = 2 * root;
    while (child <= n) {
        if ((child < n) && (a[child].key > a[child + 1].key))
            child++;
        if (rootkey < a[child].key) break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

int heapSort(element a[], int n){
    int i=n/2, j=n-1;
    element temp;
    int k = 1;
    while (i) {
        printf("adjust %d: ", k++);
        adjust(a, i--, n);
    }
    while (j) {
        SWAP(a[1], a[j + 1], temp);
        printf("adjust %d: ", k++);
        adjust(a, 1, j--);
    }
}

void main() {
    FILE* fp = fopen("in.txt", "r");
    int cnt;
    fscanf(fp, "%d", &cnt);
    element* arr = (element*)calloc(cnt + 1, sizeof(element));
    for (int i = 1;i < cnt + 1;i++) {
        fscanf(fp, "%s %d", arr[i].data, &arr[i].key);
    }
    printf("[after heap sort]\n");
    heapSort(arr, cnt);
    printf("\n");
    printarr(arr, cnt);
    free(arr);
}