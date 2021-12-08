#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char data[100];
}element;

void printarr(int arr[], int n) {
    for (int i = 0;i < n;i++) {
        printf("%4d ", arr[i]);
    }
    printf("\n");
}

int comp(int a, int b) {
    return a < b ? -1 : a > b;
}

element* merge(element a1[], int n1, element a2[], int n2) {
    if (n2==0) return NULL;
    int i = 0, j = 0;
    element* temp = (element*)malloc(sizeof(element) * (n1+n2));
    int index = 0;
    while (i < n1 && j < n2) {
        switch (comp(a1[i].key, a2[j].key)) {
        case -1:
            temp[index++] = a1[i++];
            break;
        case 0: temp[index++] = a1[i++];
        case 1:
            temp[index++] = a2[j++];
            break;
        }
    }
    for (; i < n1; temp[index++] = a1[i++]);
    for (; j < n2; temp[index++] = a2[j++]);
    printarr(temp, n1 + n2);
    return temp;

}

element* rms(element a1[],int n1,element a2[],int n2) {
    if (n2 == 0) {
        printf("b ");
        return a1;
    }
    printf("%d %d %d %d %d %d %d %d %d\n", a1[0].key, n1 / 2, a1[n1 / 2].key, n1 - 1, n1, a2[0].key, n2 / 2, a2[n1 / 2].key, n2 - 1, n2);
    return merge(rms(a1, n1 / 2, &a1[n1 / 2], n1 - 1), n1, rms(a2, n2 / 2, &a2[n1 / 2], n2 - 1), n2);
}

void main() {
    FILE* fp = fopen("in.txt", "r");
    int cnt;
    fscanf(fp, "%d", &cnt);
    element* arr = (element*)calloc(cnt, sizeof(element));
    for (int i = 0;i < cnt;i++) {
        fscanf(fp, "%s %d", arr[i].data, &arr[i].key);
    }
    printf("[after merge sort]\n");
    rms(arr, cnt/2, &arr[cnt/2], cnt-cnt/2);
    printf("\n");
    printarr(arr,cnt);
    free(arr);
}