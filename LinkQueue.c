//
//  链队列 LinkQueue
//
//  Created by 巫瑞轩 on 2021/9/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node *next;
} Node;

typedef struct link_queue {
	Node head, *tail;
	int length;
} LinkQueue;

Node *getNewNode(int);
LinkQueue *init();
void clearNode(Node *);
void clear(LinkQueue *);
int push(LinkQueue *, int);
int pop(LinkQueue *);
int isEmpty(LinkQueue *);
int front(LinkQueue *);
void output(LinkQueue *);

int main(int argc, char const *argv[])
{
	srand(time(0));
	#define MAX_OP 20
	LinkQueue *q = init();
	for (int i = 0; i < MAX_OP; i++) {
		int op = rand() % 4;
		int val = rand() % 100;
		switch (op) {
			case 0:
			case 1:
			case 2: {
				printf("push %d to Queue = %d\n", val, push(q, val));
			}
				break;
			case 3: {
				if (isEmpty(q)) {
					printf("fail to pop a item!\n");
				}
				else {
					printf("success to pop a item: %d\n", front(q));
					pop(q);
				}
			}
				break;
		}
		output(q), printf("\n");
	}
	#undef MAX_OP
	clear(q);
	return 0;
}

Node *getNewNode(int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->next = NULL;
	return p;
}

LinkQueue *init() {
	LinkQueue *q = (LinkQueue *)malloc(sizeof(LinkQueue));
	q->head.next = NULL;
	q->tail = &(q->head);
	q->length = 0;
	return q;
}

void clearNode(Node *node) {
	if (node == NULL) return;
	free(node);
	return;
}

void clear(LinkQueue *q) {
	if (q == NULL) return;
	Node *p = q->head.next, *temp;
	while (p != NULL) {
		temp = p->next;
		clearNode(p);
		p = temp;
	}
	free(q);
	return;
}

int push(LinkQueue *q, int val) {
	if (q == NULL) return 0;
	Node *node = getNewNode(val);
	q->tail->next = node;
	q->tail = node;
	q->length += 1;
	return 1;
}

int pop(LinkQueue *q) {
	if (q == NULL) return 0;
	if (isEmpty(q)) return 0;
	Node *temp = q->head.next;
	q->head.next = temp->next;
	clearNode(temp);
	q->length -= 1;
	if (q->length == 0) q->tail = &(q->head);
	return 1;
}

int isEmpty(LinkQueue *q) {
	return q->length == 0;
}

int front(LinkQueue *q) {
	return q->head.next->data;
}

void output(LinkQueue *q) {
	printf("Queue(%d): [", q->length);
	for (Node *p = q->head.next; p != NULL; p = p->next) {
		p != q->head.next && printf(" ");
		printf("%d", p->data);
	}
	printf("]\n");
	return;
}
