//
//  链表 List
//
//  Created by 巫瑞轩 on 2021/9/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node *next;
} Node;

typedef struct list {
	Node head; // 虚拟头节点（默认指向链表第一个节点）
	int length; // 链表长度
} List;

Node *getNewNode(int);
List *init();
void clearNode(Node *);
void clear(List *);
int insert(List *, int, int);
int erase(List *, int);
void reverse(List *);
void output(List *);

int main(int argc, char const *argv[]) {
	srand(time(0));
	#define MAX_OP 20
	List *l = init();
	for (int i = 0; i < MAX_OP; i++) {
		int op = rand() % 4;
		int val = rand() % 100;
		int idx = rand() % (l->length + 3) - 1;
		switch (op) {
			case 0:
			case 1: {
				printf("insert %d at %d to List = %d\n", val, idx, insert(l, idx, val));
			}
				break;
			case 2: {
				printf("reverse the List!\n");
				reverse(l);
			}
				break;
			case 3: {
				printf("erase a item at %d from List = %d\n", idx, erase(l, idx));
			}
				break;
		}
		output(l), printf("\n");
	}
	#undef MAX_OP;
	clear(l);
	return 0;
}

// 新建节点
Node *getNewNode(int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->next = NULL;
	return p;
}

// 初始化链表
List *init() {
	List *l = (List *)malloc(sizeof(List));
	l->head.next = NULL;
	l->length = 0;
	return l;
}

// 销毁单个节点
void clearNode(Node *node) {
	if (node == NULL) return;
	free(node);
	return;
}

// 销毁
void clear(List *l) {
	if (l == NULL) return;
	Node *p = l->head.next, *q;
	// 从头往后依次删除节点
	while (p != NULL) {
		q = p->next;
		clearNode(p);
		p = q;
	}
	// 最后释放链表
	free(l);
	return;
}

// 插入
int insert(List *l, int idx, int val) {
	if (l == NULL) return 0;
	if (idx < 0 || idx > l->length) return 0;
	Node *p = &(l->head), *node = getNewNode(val);
	// 头节点地址的指针初始指向链表下标0的位置，将该指针向前移动idx步到插入位置
	while (idx--) p = p->next;
	node->next = p->next;
	p->next = node;
	l->length += 1;
	return 1;
}

// 删除
int erase(List *l, int idx) {
	if (l == NULL) return 0;
	if (idx < 0 || idx >= l->length) return 0;
	Node *p = &(l->head), *q;
	while (idx--) p = p->next;
	q = p->next;
	p->next = q->next;
	clearNode(q);
	l->length -= 1;
	return 1;
}

// 翻转
void reverse(List *l) {
	if (l == NULL) return;
	Node *p = l->head.next, *q;
	l->head.next = NULL;
	// 采用头插法
	while (p != NULL) {
		q = p->next;
		p->next = l->head.next;
		l->head.next = p;
		p = q;
	}
	return;
}

// 输出
void output(List *l) {
	if (l == NULL) return;
	printf("list(%d) : ", l->length);
	for (Node *p = l->head.next; p != NULL; p = p->next) {
		printf("%d->", p->data);
	}
	printf("NULL\n");
	return;
}
