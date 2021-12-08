#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 101

typedef struct {
    int row;
    int col;
    int value;
}matrix;

matrix a[MAX_COL];
matrix b[MAX_COL];

void fastTranspose(matrix a[], matrix b[]){
    int rowTerms[MAX_COL], startingPos[MAX_COL];

    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols; b[0].col = a[0].row;
    b[0].value = numTerms;
    if (numTerms > 0) {
        for (i = 0;i < numCols;i++)
            rowTerms[i] = 0;
        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;
        for (i = 1;i < numCols;i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        for (i = 1;i <= numTerms;i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col; b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void printMatrix(matrix* m) {
    int temp = 1;
    for (int i = 0;i < m[0].row;i++) {
        for (int j = 0;j < m[0].col;j++) {
            if (m[temp].row == i && m[temp].col == j) {
                printf(" %2d", m[temp].value);
                temp++;
            }
            else
                printf("  0");
        }
        printf("\n");
    }
}

void printMatrix2(matrix* m) {
    int arr[MAX_COL][MAX_COL] = { 0 };
    for (int i = 1;i < m[0].value+1;i++) {
        arr [m[i].row][m[i].col] = m[i].value;
    }
    for (int i = 0;i < m[0].row;i++) {
        for (int j = 0;j < m[0].col;j++) {
                printf(" %2d",arr[i][j]);
        }
        printf("\n");
    }
}

int main(){
    FILE* fp1 = fopen("m1.txt", "r");
    int c = 0;
    while (!feof(fp1)) {
        int k = fscanf(fp1, "%d %d %d", &a[c].row, &a[c].col, &a[c].value);
        c++;
    }
    fclose(fp1);


    fastTranspose(a, b);
    printf("Before Transposing\n");
    printMatrix2(a);

    printf("\nAfter Transposing\n");
    printMatrix2(b);
}