// KNU CSE 2021114026 Jeongwoo Kim
// Problem 02 source code
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void arrAlloc(int*** array, int row, int col) {
    *array = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < col; i++) {
        (*array)[i] = (int*)malloc(sizeof(int) * col);
    }

    return;
}

void fillArray(int** array, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            array[i][j] = (int)pow(i, 2) + (int)pow(j, 2);
        }
    }

    return;
}

void freeArray(int** target, int row) {
    printf("free arr[%d]\n", row);
    free((*target)[row]);

    return;
}

int main(void)
{
    int row = 0, col = 0;
    int** twoDimArr = NULL;

    printf("row size: ");
    scanf("%d", &row);
    printf("col size: ");
    scanf("%d", &col);

    arrAlloc(&twoDimArr, row, col);
    fillArray(twoDimArr, row, col);

    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            printf(" %d ", twoDimArr[j][i]);
        }
        puts("");
    }

    /*
    for (int i = 0; i < row; i++) {
       freeArray(&twoDimArr[i], i);
    }
    */
    for (int i = 0; i < row; i++) {
        printf("free arr[%d].\n", i);
        free(*(twoDimArr + i));
    }
    free(twoDimArr);
    printf("free arr.\n");

    return 0;
}