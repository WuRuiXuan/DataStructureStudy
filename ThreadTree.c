//
//  二叉树线索化 ThreadTree
//
//  Created by 巫瑞轩 on 2021/9/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 度为0的节点比度为2的节点多1个，如果按每个节点固定有两条边算，则有一半以上的边处于空余状态，而线索化就是利用这些空余的边来建立遍历二叉排序树的路线
// 遍历的起点一定是最左且度为0的子节点

// 标记普通节点
#define NORMAL 0
// 标记后继节点
#define THREAD 1

typedef struct node {
	int data;
	struct node *lchild, *rchild;
	int ltag, rtag;
} Node;

Node *getNewNode(int);
Node *insert(Node *, int);
void buildThread(Node *);
void output(Node *);
Node *mostLeft(Node *);
void inOrder(Node *);
void clear(Node *);

int main(int argc, char const *argv[]) {
	srand(time(0));
	#define MAX_OP 20
	Node *root = NULL;
	for (int i = 0; i < MAX_OP; i++) {
		int val = rand() % 100;
		root = insert(root, val);
	}
	buildThread(root);
	output(root), printf("\n");
	inOrder(root), printf("\n");
	clear(root);
	return 0;
}

Node *getNewNode(int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->lchild = NULL;
	p->rchild = NULL;
	p->ltag = NORMAL;
	p->rtag = NORMAL;
	return p;
}

Node *insert(Node *root, int val) {
	if (root == NULL) return getNewNode(val);
	if (root->data == val) return root;
	if (val < root->data) root->lchild = insert(root->lchild, val);
	else root->rchild = insert(root->rchild, val);
	return root;
}

void buildThread(Node *root) {
	if (root == NULL) return;
	// 前驱节点
	static Node *pre = NULL;
	// 添加线索顺序：左子树 - 根节点 - 右子树
	buildThread(root->lchild);
	if (root->lchild == NULL) {
		root->lchild = pre;
		root->ltag = THREAD;
	}
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = root;
		pre->rtag = THREAD;
	}
	pre = root;
	buildThread(root->rchild);
	return;
}

// 线索化中序遍历（效率更高）
void output(Node *root) {
	Node *p = mostLeft(root);
	while (p != NULL) {
		printf("%d ", p->data);
		if (p->rtag == THREAD) {
			p = p->rchild;
		}
		else {
			p = mostLeft(p->rchild);
		}
	}
	return;
}

Node *mostLeft(Node *p) {
	while (p != NULL && p->ltag == NORMAL && p->lchild != NULL) p = p->lchild;
	return p;
}

// 递归中序遍历（树深度太深可能会有爆栈的风险）
void inOrder(Node *root) {
	if (root == NULL) return;
	if (root->ltag == NORMAL) inOrder(root->lchild);
	printf("%d ", root->data);
	if (root->rtag == NORMAL) inOrder(root->rchild);
	return;
}

void clear(Node *root) {
	if (root == NULL) return;
	if (root->ltag == NORMAL) clear(root->lchild);
	if (root->rtag == NORMAL) clear(root->rchild);
	free(root);
	return;
}
