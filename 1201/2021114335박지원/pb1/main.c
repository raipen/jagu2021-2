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
    element* temp = (element*)malloc(sizeof(element) * (c - a));//a���� c-1������ arr ������ �����Ͽ� ������ �迭�̹Ƿ� c-a���� ������ �Ҵ�
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
    while (n < length) {    //�迭�� 2���� ��� ����->4���� ��� ����-> .... ->length��ŭ ����
        for (int i = 0;i < length;i += n * 2) { //�迭�� n*2�� ��ŭ ��� ����
            element* temp = merge(arr, i, i + n < length ? i + n : length, i + 2 * n < length ? i + 2 * n : length);
            /*i�������� 2n����ŭ �����ϴµ�,
            ���� ������ �κ��̶� n���� 2n������ ���� ���,
            �� ������ �κб����� ������ �� �ֵ��� length�� ���ڷ� ����*/
            if (temp)   //�������� ©�� �κ��� n������ �۰ų� ���Ƽ� ������ �ٲ��� ���� ��쿣 �ǳ� ��
                for (int j = i;j < (i + 2 * n < length ? i + 2 * n : length);j++)   //������ �κб���
                    arr[j] = temp[j - i];   //���� �迭�� ����
            free(temp); //temp�� ������ ���� �迭�� ����������, ��������� temp�� �Ҵ�� �޸𸮸� ����
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