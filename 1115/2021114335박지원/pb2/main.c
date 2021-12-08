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
    return (ptr == NULL) ? true : false;
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

bst* parents_of_left_max_node(bst** head) {
    bst* temp = (*head)->left;
    if (temp->right == NULL) {
        return (*head);
    }

    while (temp->right->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

void Delete_bst(bst** head, element k) {
    if ((*head) == NULL) return;
    bst* cur = (*head);
    bst* prv = NULL;
    while (cur != NULL) {
        if (cur->data == k) {   //현재 노드를 삭제하는 경우
            if (cur->left != NULL && cur->right != NULL) { //현재 노드의 양쪽 자식 모두 존재
                bst* temp = parents_of_left_max_node(&cur); // 왼쪽에 있는 노드 중 가장 큰 값을 가진 노드의 부모를 반환
                if (temp == cur) {
                    cur->data = temp->left->data;
                    cur->left = temp->left->left;
                }
                else {
                    cur->data = temp->right->data;
                    temp->right = temp->right->left;
                }
            }
            else {//현재 노드의 자식 노드가 0~1개
                if (!prv) {
                    *head = (*head)->left == NULL ? (*head)->right : (*head)->left;
                }
                else if (k < prv->data) 
                    prv->left = cur->left == NULL ? cur->right : cur->left;
                else
                    prv->right = cur->left == NULL ? cur->right : cur->left;
            }
            return;
        }//현재 노드를 삭제하는 경우 끝
        if (cur->data > k) {
            prv = cur;
            cur = cur->left;
        }
        else if (cur->data < k) {
            prv = cur;
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
    FILE* fp = fopen("in2.txt", "r");
    int a;
    bst* root = Create_bst();
    while (!feof(fp)) {
        fscanf(fp, "%d ", &a);
        Insert_bst(&root, a);
    }
    printf("Binary search tree(Inorder)\n");
    inorder(root);
    fclose(fp);

    while (1) {
        printf("\ndelete number:");
        scanf("%d", &a);
        if (a < 0) break;
        Delete_bst(&root, a);
        inorder(root);
    }
}