#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char data[100];
}element;

void printarr(element arr[], int n) {
    for (int i = 0;i < n;i++) {
        printf("%6s:%4d\n", arr[i].data, arr[i].key);
    }
}

int comp(int a, int b) {
    return a < b ? -1 : a > b;
}

element* merge(element arr[], int a, int b, int c) {
    if (b >= c) return NULL;    //
    int i = a, j = b;
    element* temp = (element*)malloc(sizeof(element) * (c - a));//a부터 c-1까지의 arr 공간을 정렬하여 저장할 배열이므로 c-a개의 공간을 할당
    int index = 0;
    while (i < b && j < c) {
        switch (comp(arr[i].key, arr[j].key)) {
        case -1:
            temp[index++] = arr[i++];
            break;
        case 0: temp[index++] = arr[i++];
        case 1:
            temp[index++] = arr[j++];
            break;
        }
    }
    for (; i < b; temp[index++] = arr[i++]);
    for (; j < c; temp[index++] = arr[j++]);
    return temp;
}

void mergeSort(element arr[], int length) {
    int n = 1;
    while (n < length) {    //배열을 2개씩 끊어서 정렬->4개씩 끊어서 정렬-> .... ->length만큼 정렬
        for (int i = 0;i < length;i += n * 2) { //배열을 n*2개 만큼 끊어서 정렬
            element* temp = merge(arr, i, i + n < length ? i + n : length, i + 2 * n < length ? i + 2 * n : length);
            /*i에서부터 2n개만큼 정렬하는데,
            만약 마지막 부분이라 n개나 2n개보다 적은 경우,
            그 마지막 부분까지만 정렬할 수 있도록 length를 인자로 전달*/
            if (temp)   //마지막에 짤린 부분이 n개보다 작거나 같아서 정렬이 바뀌지 않은 경우엔 건너 뜀
                for (int j = i;j < (i + 2 * n < length ? i + 2 * n : length);j++)   //정렬한 부분까지
                    arr[j] = temp[j - i];   //원래 배열에 복사
            free(temp); //temp의 내용을 원래 배열에 복사했으니, 쓸모없어진 temp에 할당된 메모리를 해제
        }
        n = n * 2;
    }
}

void main() {
    FILE* fp = fopen("in.txt", "r");
    int cnt;
    fscanf(fp, "%d", &cnt);
    element* arr = (element*)malloc(sizeof(element) * cnt);
    for (int i = 0;i < cnt;i++) {
        fscanf(fp, "%s %d", arr[i].data, &arr[i].key);
    }
    printf("[after merge sort]\n");
    mergeSort(arr, cnt);
    printarr(arr, cnt);
    free(arr);
}