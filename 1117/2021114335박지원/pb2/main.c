#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* NODE;
struct node {
    int ver;
    NODE link;
};

int n;
NODE g[10], invg[10];

void insert(NODE* head, int v) {
    if (!(*head)) {
        (*head) = (NODE)malloc(sizeof(struct node));
        (*head)->ver = v;
        (*head)->link = NULL;
    }
    else {
        NODE t = (NODE)malloc(sizeof(struct node));
        t->ver = v;
        t->link = (*head);
        (*head) = t;
    }
}

void print() { //adj
    printf("(1) Adjacency Matrix");
    for (int i = 0; i < n; i++) {
        printf("\n");
        NODE cur = g[i];    
        for (int j = 0; j < n; j++) {
            if (cur->ver == j) {
                printf("%2d", 1);
                cur = cur->link;
            }
            else printf("%2d", 0);
        }
    }
}
void outd() { //linked
    printf("\n(5) Outdegree");
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        NODE cur = g[i];
        while (cur) {
            cnt++;
            cur = cur->link;
        }
        printf("\n[%2d] %d", i, cnt);
    }
}

void ind() { //inverse
    printf("\n(4) Indegree");
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        NODE cur = invg[i];
        while (cur) {
            cnt++;
            cur = cur->link;
        }
        printf("\n[%2d] %d", i, cnt);
    }
}

void link() {
    printf("\n(2) Linked Adjacency List");
    for (int i = 0; i < n; i++) {
        printf("\n[%2d]", i);
        NODE cur = g[i];
        while (cur != NULL) {
            printf("%3d", cur->ver);
            cur = cur->link;
        }
    }
}

void inverse() {
    printf("\n(3) Inverse Adjacency List");
    for (int i = 0; i < n; i++) {
        printf("\n[%2d]", i);
        NODE cur = invg[i];
        while (cur != NULL) {
            printf("%3d", cur->ver);
            cur = cur->link;
        }
    }
}

int main() {
    int in, out;
    FILE* fp = fopen("in.txt", "r");
    fscanf(fp, "%d", &n);

    while (!feof(fp)) {
        fscanf(fp, "%d %d", &out, &in);
        printf("%d %d\n", in, out);
        insert(&g[out], in);
        insert(&invg[in], out);
    }

    //print();
    link();
    inverse();
    ind();
    outd();

    fclose(fp);
}