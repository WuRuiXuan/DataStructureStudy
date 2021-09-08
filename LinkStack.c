//
//  链栈 LinkStack
//
//  Created by 巫瑞轩 on 2021/9/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node *next;
} Node;

typedef struct link_stack {
	Node head;
	int size;
} LinkStack;

Node *getNewNode(int);
LinkStack *init(int);
void clearNode(Node *);
void clear(LinkStack *);
int push(LinkStack *, int);
int pop(LinkStack *);
int isEmpty(LinkStack *);
int top(LinkStack *);
void output(LinkStack *);

int main(int argc, char const *argv[])
{
	srand(time(0));
	#define MAX_OP 20
	LinkStack *s = init(1);
	for (int i = 0; i < MAX_OP; i++) {
		int op = rand() % 4;
		int val = rand() % 100;
		switch (op) {
			case 0:
			case 1:
			case 2: {
				printf("push %d to Stack = %d\n", val, push(s, val));
			} break;
			case 3: {
				if (isEmpty(s)) {
					printf("fail to pop!\n");
				} else {
					printf("success to pop: %d\n", top(s));
					pop(s);
				}
			} break;
		}
		output(s), printf("\n");
	}
	#undef MAX_OP
	clear(s);
	return 0;
}

Node *getNewNode(int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->next = NULL;
	return p;
}

LinkStack *init() {
	LinkStack *s = (LinkStack *)malloc(sizeof(LinkStack));
	s->head.next = NULL;
	s->size = 0;
	return s;
}

void clearNode(Node *node) {
	if (node == NULL) return;
	free(node);
	return;
}

void clear(LinkStack *s) {
	if (s == NULL) return;
	Node *p = s->head.next, *temp;
	while (p != NULL) {
		temp = p->next;
		clearNode(p);
		p = temp;
	}
	free(s);
	return;
}

int push(LinkStack *s, int val) {
	if (s == NULL) return 0;
	Node *node = getNewNode(val);
	node->next = s->head.next;
	s->head.next = node;
	s->size += 1;
	return 1;
}

int pop(LinkStack *s) {
	if (s == NULL) return 0;
	if (isEmpty(s)) return 0;
	Node *temp = s->head.next;
	s->head.next = temp->next;
	clearNode(temp);
	s->size -= 1;
	return 1;
}

int isEmpty(LinkStack *s) {
	return s->size == 0;
}

int top(LinkStack *s) {
	return s->head.next->data;
}

void output(LinkStack *s) {
	printf("Stack: [");
	int *num = (int *)malloc(sizeof(int) * s->size);
	int i = s->size - 1;
	for (Node *p = s->head.next; p != NULL; p = p->next) {
		num[i] = p->data;
		i --;
	}
	for (int j = 0; j < s->size; j++) {
		j && printf(" ");
		printf("%d", num[j]);
	}
	printf("]\n");
	return;
}
