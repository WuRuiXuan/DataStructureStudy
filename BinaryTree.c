//
//  二叉排序树（左节点值 < 根节点值 < 右节点值） BinaryTree
//
//  Created by 巫瑞轩 on 2021/9/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node *lchild, *rchild;
} Node;

typedef struct tree {
	Node *root;
	int length;
} Tree;

Node *getNewNode(int);
Tree *init();
Node *insertNode(Node *, int, int *);
void insert(Tree *, int);
void clearNode(Node *);
void clear(Tree *);
void preOrder(Tree *);
void preOrderNode(Node *);
void inOrder(Tree *);
void inOrderNode(Node *);
void postOrder(Tree *);
void postOrderNode(Node *);
void output(Tree *);
void outputNode(Node *);

int main(int argc, char const *argv[]) {
	srand(time(0));
	Tree *t = init();
	#define MAX_OP 20
	for (int i = 0; i < MAX_OP; i++) {
		int val = rand() % 100;
		insert(t, val);
		output(t);
	}
	preOrder(t);
	inOrder(t);
	postOrder(t);
	clear(t);
	#undef MAX_OP
	return 0;
}

Node *getNewNode(int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->lchild = p->rchild = NULL;
	return p;
}

Tree *init() {
	Tree *t = (Tree *)malloc(sizeof(Tree));
	t->root = NULL;
	t->length = 0;
	return t;
}

Node *insertNode(Node *root, int val, int *flag) {
	if (root == NULL) {
		*flag = 1;
		return getNewNode(val);
	}
	if (root->data == val) return root;
	if (root->data > val) root->lchild = insertNode(root->lchild, val, flag);
	else root->rchild = insertNode(root->rchild, val, flag);
	return root;
}

void insert(Tree *t, int val) {
	if (t == NULL) return;
	int flag = 0;
	t->root = insertNode(t->root, val, &flag);
	t->length += flag;
	return;
}

void clearNode(Node *root) { // 传入树的根节点
	if (root == NULL) return;
	clearNode(root->lchild);
	clearNode(root->rchild);
	free(root);
	return;
}

void clear(Tree *t) {
	if (t == NULL) return;
	clearNode(t->root);
	free(t);
	return;
}

// 前序遍历（根节点 -> 左节点 -> 右节点）
void preOrder(Tree *t) {
	if (t == NULL) return;
	printf("preOrder: ");
	preOrderNode(t->root);
	printf("\n");
	return;
}

void preOrderNode(Node *root) {
	if (root == NULL) return;
	printf("%d ", root->data);
	preOrderNode(root->lchild);
	preOrderNode(root->rchild);
	return;
}

// 中序遍历（左节点 -> 根节点 -> 右节点）
void inOrder(Tree *t) {
	if (t == NULL) return;
	printf("inOrder: ");
	inOrderNode(t->root);
	printf("\n");
	return;
}

void inOrderNode(Node *root) {
	if (root == NULL) return;
	inOrderNode(root->lchild);
	printf("%d ", root->data);
	inOrderNode(root->rchild);
	return;
}

// 后序遍历（左节点 -> 右节点 -> 根节点）
void postOrder(Tree *t) {
	if (t == NULL) return;
	printf("postOrder: ");
	postOrderNode(t->root);
	printf("\n");
	return;
}

void postOrderNode(Node *root) {
	if (root == NULL) return;
	postOrderNode(root->lchild);
	postOrderNode(root->rchild);
	printf("%d ", root->data);
	return;
}

void output(Tree *t) {
	if (t == NULL) return;
	printf("tree(%d): ", t->length);
	outputNode(t->root);
	printf("\n");
	return;
}

void outputNode(Node *root) {
	if (root == NULL) return;
	printf("%d", root->data);
	if (root->lchild == NULL && root->rchild == NULL) return;
	printf("(");
	outputNode(root->lchild);
	printf(",");
	outputNode(root->rchild);
	printf(")");
	return;
}
