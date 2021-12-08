#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int contents;
typedef struct t {
	struct t* left;
	contents value;
	struct t* right;
}tree;

void addLeft(tree* cur,contents value) {
	cur->left = (tree*)malloc(sizeof(tree));
	cur->left->value = value;
	cur->left->left = NULL;
	cur->left->right = NULL;
}

void addRight(tree* cur, contents value) {
	cur->right = (tree*)malloc(sizeof(tree));
	cur->right->value = value;
	cur->right->left = NULL;
	cur->right->right = NULL;
}


tree* makeTree() {
	tree* root = (tree*)malloc(sizeof(tree));
	int i = 0;
	root->value = i++;
	root->left = NULL;
	root->right = NULL;
	addLeft(root, i++);
	addRight(root, i++);
	addLeft(root->left, i++);
	addLeft(root->right, i++);
	addRight(root->right, i++);
	addRight(root->left->left, i++);
	addLeft(root->right->left, i++);
	addRight(root->right->left, i++);
	addRight(root->right->left->right, i++);
	return root;
}

void inorder(tree* root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}
}

void preorder(tree* root) {
	if (root){
		printf("%d ", root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(tree* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->value);
	}
}

void main() {
	tree* root = makeTree();
	printf("inorder:");
	inorder(root);
	printf("\npreorder:");
	preorder(root);
	printf("\npostorder:");
	postorder(root);
}