#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
#define MAX_VERTICES 6

typedef int element;

typedef struct {
    element** data;
    int size;
}Adj_matrix;

typedef struct {
    int size;
    int* path;
    int* length;
}path;

int cost[][MAX_VERTICES] = {
   {0, 100, 150, MAX, MAX, MAX},
   {MAX, 0, MAX, 120, MAX, 150},
   {MAX, MAX, 0, MAX, 100, MAX},
   {MAX, MAX, MAX, 0, 20, 10},
   {MAX, MAX, MAX, MAX, 0, MAX},
   {MAX, MAX, MAX, MAX, 60, 0}
};

Adj_matrix newAM() {
    Adj_matrix temp;
    temp.size = MAX_VERTICES;
    temp.data = (int**)malloc(sizeof(int*) * temp.size);
    for (int i = 0;i < temp.size;i++) {
        temp.data[i] = (int*)calloc(temp.size, sizeof(int));
    }
    for (int i = 0;i < temp.size;i++) {
        for (int j = 0;j < temp.size;j++) {
            temp.data[i][j] = cost[i][j];
        }
    }
    return temp;
}

void printAM(Adj_matrix this) {
    for (int i = 0;i < this.size;i++) {
        for (int j = 0;j < this.size;j++) {
            printf("%4d  ", this.data[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(Adj_matrix am) {
    for (int i = 0;i < am.size;i++) {
        free(am.data[i]);
    }
    free(am.data);
}

path newPath(int size) {
    path temp;
    temp.length = (int*)malloc(sizeof(int) * size);
    temp.path = (int*)calloc(size, sizeof(int));
    temp.size = size;
    return temp;
}

int noVisitedMin(int length[], int visited[], int size) {
    int init = 1;
    int min;
    for (int i = 0;i < size;i++) {
        if (init && !visited[i]) {
            min = i;
            init = 0;
        }
        else if (!init && !visited[i] && length[min] > length[i]) {
            min = i;
        }
    }
    return min;
}

path findPath(Adj_matrix am,int input) {
    path result = newPath(am.size);
    int* visited= (int*)calloc(am.size,sizeof(int));
    visited[input] = 1;
    for (int i = 0;i < am.size;i++) {
        result.length[i] = am.data[input][i];
        result.path[i] = input;
    }
    for (int i = 0;i < am.size-1;i++) {
        int cur = noVisitedMin(result.length, visited,am.size);
        visited[cur] = 1;
        for (int j = 0;j < am.size;j++) {
            if (!visited[j]) {
                if (result.length[j] > result.length[cur] + am.data[cur][j]) {
                    result.length[j] = result.length[cur] + am.data[cur][j];
                    result.path[j] = cur;
                }
            }
        }
    }

    return result;
}


void printPath2(path result, int i,int input) { //printPath 함수에서 호출 되는 함수
    if (i == input) {
        return;
    }
    printPath2(result, result.path[i],input);
    printf("%2d", i);
}

int printPath3(path result, int i, int input) { // 안 쓰는 함수, 이걸 써도 정상 작동합니다, 정상작동 시 사용 예시는 printPath에 주석처리해놨습니다.
    if (result.path[i] == input) {
        return i;
    }
    printf("%2d", printPath3(result, result.path[i], input));
    return i;
}

void printPath(path result,int input) { //main에서 호출되는 함수
    printf("[Cost: Path from vertex %d]\n", input, input);
    for (int i = 0;i < result.size;i++) {
        if (i == input)
            continue;
        printf("[to %d] ", i);
        if (result.length[i] == MAX) {
            printf("No path.\n");
            continue;
        }
        printf("cost :%3d path:", result.length[i]);
        printPath2(result, i,input);
        //printf("%2d", printPath3(result, i, input));
        printf("\n");
    }
}


void main() {
    Adj_matrix am = newAM();
    int input;
    printf("Start node:");
    scanf("%d", &input);
    path result = findPath(am, input);
    printPath(result,input);
    freeMatrix(am);
}