#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef enum { false, true } boolean;
typedef struct t {
    struct t* left, * right;
    element data;
}tree;
typedef tree bst;

bst* Create_bst() {
    bst* head = NULL;
    return head;
}

boolean IsEmpty_bst(bst* ptr) {
    return (ptr == NULL) ? true: false;
}

element* Search_bst(bst* head, element k) {
    if (!head) return NULL;
    if (k == head->data) return &(head->data);
    if (k < head->data) return Search_bst(head->left, k);
    else return Search_bst(head->right, k);
}

element* iterSearch_bst(bst* head, element k) {
    bst* cur = head;
    while (cur != NULL) {
        if (k == cur->data) return &(cur->data);
        else if (k < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    return NULL;
}

bst* itermodifiedSearch_bst(bst* head, element k) {
    bst* cur = head;
    while (cur != NULL) {
        if (k == cur->data) return NULL;
        else if (k < cur->data) {
            if (cur->left == NULL)
                return cur;
            cur = cur->left;
        }
        else {
            if (cur->right == NULL)
                return cur;
            cur = cur->right;
        }
    }
}

void Insert_bst(bst** head, element k) {
    bst* temp = itermodifiedSearch_bst(*head, k);

    bst* ptr = (bst*)malloc(sizeof(bst));
    ptr->data = k;
    ptr->left = ptr->right = NULL;

    if (!(*head)) {
        *head = ptr;
        return;
    }
    if (temp) {
        if (k < temp->data) temp->left = ptr;
        else temp->right = ptr;
    }
}

void inorder(bst* head) {
    if (!head) return;
    inorder(head->left);
    printf("%4d", head->data);
    inorder(head->right);
}

void main() {
    FILE* fp = fopen("in1.txt", "r");
    int a;
    bst* root = Create_bst();
    while (!feof(fp)) {
        fscanf(fp, "%d ", &a);
        Insert_bst(&root, a);
    }
    printf("Binary search tree(Inorder):\n");
    inorder(root);
    fclose(fp);

    printf("\n\n");
    fp = fopen("search.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%d ", &a);
        printf("%2d: %c\n", a, Search_bst(root, a) ? 'O' : 'X');
    }
    fclose(fp);
}