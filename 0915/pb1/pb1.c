#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100 /*size of terms array*/
typedef struct {
    int coef;
    int expon;
} term;
term terms[MAX_TERMS];

typedef struct {
    int s;
    int f;
} index;

void printexpression(index n) {
    if (n.s > n.f) {
        printf("0\n");
        return;
    }
    for (int i = n.s;i < n.f+1;i++) {
            printf("%dx^%d%s", terms[i].coef, terms[i].expon,i!=n.f?" + ":"\n");
    }
}

void padd(index a,index b,index* d) {
    int i = a.s, j = b.s;
    while (i <= a.f || j <= b.f) {
        //printf("%d %d\n", terms[i].expon, terms[j].expon);
        int at = i <= a.f ? terms[i].expon : -1;
        int bt = j <= b.f ? terms[j].expon : -1;
        if (at > bt) {
            d->f++;
            terms[d->f].coef = terms[i].coef;
            terms[d->f].expon = terms[i].expon;
            i++;
        }
        else if (at < bt) {
            d->f++;
            terms[d->f].coef = terms[j].coef;
            terms[d->f].expon = terms[j].expon;
            j++;
        }
        else {
            if (terms[i].coef + terms[j].coef == 0) {
                i++;
                j++;
                continue;
            }
            d->f++;
            terms[d->f].coef = terms[i].coef + terms[j].coef;
            terms[d->f].expon = terms[i].expon;
            i++;
            j++;
        }
    }
}

int main(void)
{
    index a = { 0,-1 };
    FILE* fp1 = fopen("a.txt", "r");
    while (!feof(fp1)) {
        a.f++;
        fscanf(fp1, "%d %d", &terms[a.f].coef, &terms[a.f].expon);
    }
    index b = { a.f+1,a.f};
    FILE* fp2 = fopen("b.txt", "r");
    while (!feof(fp2)) {
        b.f++;
        fscanf(fp2, "%d %d", &terms[b.f].coef, &terms[b.f].expon);
    }
    index d = { b.f + 1,b.f };

    padd(a, b, &d);

    printf("A(x):");
    printexpression(a);
    printf("B(x):");
    printexpression(b);
    printf("\nC(x):");    
    printexpression(d);
}