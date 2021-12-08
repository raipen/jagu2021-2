#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int n;
	char name[10];
} name;

void main() {
    name in[100];
    name add[100];
    FILE* fp1 = fopen("in.txt", "r");
    int c = 0;
    while (!feof(fp1)) {
        fscanf(fp1, "%d %s", &in[c].n, in[c].name);
        c++;
    }
    fclose(fp1);
    FILE* fp2 = fopen("add.txt", "r");
    int d = 0;
    while (!feof(fp2)) {
        fscanf(fp2, "%d %s", &add[d].n, add[d].name);
        d++;
    }
    fclose(fp2);

    FILE* fp3 = fopen("out.txt", "w");
    int i = 0, j = 0;
    while (i < c&&j<d) {
        if (in[i].n < add[j].n) {
            printf("%2d, %5s\n", in[i].n, in[i].name);
            fprintf(fp3,"%d %s\n", in[i].n, in[i].name);
            i++;
        } else if (in[i].n > add[j].n) {
            printf("%2d, %5s\n", add[j].n, add[j].name);
            fprintf(fp3, "%d %s\n", add[j].n, add[j].name);
            j++;
        }else {
            printf("%2d, %5s\n", in[i].n, "ERROR");
            fprintf(fp3, "%d %s\n", in[i].n, "ERROR");
            i++;
            j++;
        }
    }
    for (;i < c;i++) {
        printf("%2d, %5s\n", in[i].n, in[i].name);
        fprintf(fp3, "%d %s\n", in[i].n, in[i].name);
    }
    for (;j < d;j++) {
        printf("%2d, %5s\n", add[j].n, add[j].name);
        fprintf(fp3, "%d %s\n", add[j].n, add[j].name);
    }
}