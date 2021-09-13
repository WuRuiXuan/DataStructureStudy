//
//  广义表转二叉树 TableToTree
//
//  Created by 巫瑞轩 on 2021/9/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data;
	struct node *lchild, *rchild;
} Node;

typedef struct tree {
	Node *root;
	int length;
} Tree;

typedef struct stack {
	Node **data;
	int top, size;
} Stack;

Node *getNewNode(char);
Tree *getNewTree();
Stack *initStack(int);
Node *top(Stack *);
int isEmpty(Stack *);
int push(Stack *, Node *);
int pop(Stack *);
void clearStack(Stack *);
void clearNode(Node *);
void clearTree(Tree *);
Node *build(const char *, int *);
void preOrder(Tree *);
void preOrderNode(Node *);
void inOrder(Tree *);
void inOrderNode(Node *);
void postOrder(Tree *);
void postOrderNode(Node *);

int main(int argc, char const *argv[]) {
	char str[1000] = {0};
	int nodeNum = 0;
	// 支持读入带空格的字符串
	scanf("%[^\n]s", str);
	// 读入完成后去除手动添加的换行
	getchar();
	Tree *t = getNewTree();
	t->root = build(str, &nodeNum);
	t->length = nodeNum;
	preOrder(t);
	inOrder(t);
	postOrder(t);
	clearTree(t);
	return 0;
}

Node *getNewNode(char val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->lchild = p->rchild = NULL;
	return p;
}

Tree *getNewTree() {
	Tree *t = (Tree *)malloc(sizeof(Tree));
	t->root = NULL;
	t->length = 0;
	return t;
}

Stack *initStack(int n) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data = (Node **)malloc(sizeof(Node *) * n);
	s->top = -1;
	s->size = n;
	return s;
}

Node *top(Stack *s) {
	return s->data[s->top];
}

int isEmpty(Stack *s) {
	return s->top == -1;
}

int push(Stack *s, Node *val) {
	if (s == NULL) return 0;
	if (s->top == s->size - 1) return 0;
	s->data[++(s->top)] = val;
	return 1;
}

int pop(Stack *s) {
	if (s == NULL) return 0;
	if (isEmpty(s)) return 0;
	s->top -= 1;
	return 1;
}

void clearStack(Stack *s) {
	if (s == NULL) return;
	free(s->data);
	free(s);
	return;
}

void clearNode(Node *root) {
	if (root == NULL) return;
	clearNode(root->lchild);
	clearNode(root->rchild);
	free(root);
	return;
}

void clearTree(Tree *t) {
	if (t == NULL) return;
	clearNode(t->root);
	free(t);
	return;
}

Node *build(const char *str, int *nodeNum) {
	Stack *s = initStack(strlen(str));
	// 标记逗号
	int flag = 0;
	Node *temp = NULL, *p = NULL;
	while (str[0]) {
		switch (str[0]) {
			case '(': {
				push(s, temp);
				flag = 0;
			} break;
			case ')': {
				p = top(s);
				pop(s);
			} break;
			case ',': flag = 1; break;
			case ' ': break;
			default:
				temp = getNewNode(str[0]);
				if (!isEmpty(s) && flag == 0) {
					top(s)->lchild = temp;
				}
				else if (!isEmpty(s) && flag == 1) {
					top(s)->rchild = temp;
				}
				// 增加二叉树节点个数
				++(*nodeNum);
				break;
		}
		// 字符串地址向前移动
		str++;
	}
	clearStack(s);
	if (temp && p == NULL) p = temp;
	return p;
}

void preOrder(Tree *t) {
	if (t == NULL) return;
	printf("preOrder(%d): ", t->length);
	preOrderNode(t->root);
	printf("\n");
	return;
}

void preOrderNode(Node *root) {
	if (root == NULL) return;
	printf("%c ", root->data);
	preOrderNode(root->lchild);
	preOrderNode(root->rchild);
	return;
}

void inOrder(Tree *t) {
	if (t == NULL) return;
	printf("preOrder(%d): ", t->length);
	inOrderNode(t->root);
	printf("\n");
	return;
}

void inOrderNode(Node *root) {
	if (root == NULL) return;
	inOrderNode(root->lchild);
	printf("%c ", root->data);
	inOrderNode(root->rchild);
	return;
}

void postOrder(Tree *t) {
	if (t == NULL) return;
	printf("preOrder(%d): ", t->length);
	postOrderNode(t->root);
	printf("\n");
	return;
}

void postOrderNode(Node *root) {
	if (root == NULL) return;
	postOrderNode(root->lchild);
	postOrderNode(root->rchild);
	printf("%c ", root->data);
	return;
}
