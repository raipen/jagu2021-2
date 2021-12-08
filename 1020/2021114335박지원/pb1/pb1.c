#define _CRT_SECURE_NO_WARNINGS
#include "Linkedlist.h"
#define COMPARE(a,b) a>b?-1:(a==b?0:1)

list* set_poly_from_file(char* filename) {
    FILE* fp = fopen(filename, "r");
    list* poly = newLinkedList();
    while (!feof(fp)) {
        contents temp;
        fscanf(fp, "%d %d", &temp.coef, &temp.expon);
        insert(poly, temp, -1);            //맨 끝 노드에 추가(-1)
    }
    fclose(fp);
    return poly;
}

list* padd(list* a, list* b) {
    list* result = newLinkedList();
    node* cur_a = a->head;
    node* cur_b = b->head;
    while (cur_a != NULL && cur_b != NULL) {
        switch (COMPARE(cur_a->value.expon, cur_b->value.expon)) {
        case -1:
            insert(result, cur_a->value, -1);
            cur_a = cur_a->next;
            break;
        case 0:
            cur_a->value.coef += cur_b->value.coef;
            if (cur_a->value.coef)
                insert(result, cur_a->value, -1);
            cur_a = cur_a->next;
            cur_b = cur_b->next;
            break;
        case 1:
            insert(result, cur_b->value, -1);
            cur_b = cur_b->next;
            break;
        }
    }
    while (cur_a != NULL) {
        insert(result, cur_a->value, -1);
        cur_a = cur_a->next;
    }
    while (cur_b != NULL) {
        insert(result, cur_b->value, -1);
        cur_b = cur_b->next;
    }
    return result;
}

void main() {
    list* poly1 = set_poly_from_file("poly1.txt");
    list* poly2 = set_poly_from_file("poly2.txt");
    printf("%10s", "poly A:");
    printNode(poly1, "[%d,%d] ");
    printf("%10s", "poly B:");
    printNode(poly2, "[%d,%d] ");
    printf("%10s", "poly(A+B):");
    list* poly3 = padd(poly1, poly2);
    printNode(poly3, "[%d,%d] ");
    printf("\n");

    poly1 = deleteLinkedList(poly1);
    poly2 = deleteLinkedList(poly2);
    poly3 = deleteLinkedList(poly3);


    printf("\n삭제>>\n");
    printf("%10s", "poly A:");
    printNode(poly1, "[%d,%d] ");
    printf("%10s", "poly B:");
    printNode(poly2, "[%d,%d] ");
    printf("%10s", "poly(A+B):");
    printNode(poly3, "[%d,%d] ");
    printf("\n");
}