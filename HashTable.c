//
//  哈希表（拉链法） HashTable
//
//  Created by 巫瑞轩 on 2021/10/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *str;
	struct node *next;
} Node;

typedef struct hashTable {
	Node **data;
	int size;
} HashTable;

Node *initNode(char *, Node *);
HashTable *initHashTable(int);
int BKDRHash(char *);
void insert(HashTable *, char *);
int search(HashTable *, char *);
void clearNode(Node *);
void clear(HashTable *);

int main(int argc, char const *argv[])
{
	int op;
	#define MAX_N 100
	char str[MAX_N + 5] = {0};
	HashTable *h = initHashTable(MAX_N + 5);
	while (~scanf("%d%s", &op, str)) {
		switch (op) {
			case 0:
				printf("insert %s to HashTable\n", str);
				insert(h, str);
				break;
			case 1:
				printf("search %s from HashTable result = %d\n", str, search(h, str));
				break;
		}
	}
	#undef MAX_N
	clear(h);
	return 0;
}

// 初始化拉链上的节点
Node *initNode(char *str, Node *head) {
	Node *p = (Node *)malloc(sizeof(Node));
	// strdup 深拷贝字符串并返回新地址
	p->str = strdup(str);
	p->next = head;
	return p;
}

// 初始化哈希表
HashTable *initHashTable(int n) {
	HashTable *h = (HashTable *)malloc(sizeof(HashTable));
	// 将容量扩大一倍，实现的哈希表大约达到50%的利用率（工业级：70% ~ 90%）
	h->size = n << 1;
	h->data = (Node **)calloc(h->size, sizeof(Node *));
	return h;
}

int BKDRHash(char *str) {
	int seed = 31, hash = 0;
	for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
	// hash可能为负数，因此要进行与操作
	return hash & 0x7fffffff;
}

void insert(HashTable *h, char *str) {
	int hash = BKDRHash(str);
	int idx = hash % h->size;
	// h->data[idx] 数组第idx位上的链表的首地址
	h->data[idx] = initNode(str, h->data[idx]);
}

int search(HashTable *h, char *str) {
	int hash = BKDRHash(str);
	int idx = hash % h->size;
	Node *p = h->data[idx];
	// 依次向后比对节点的字符串和要查找的字符串，直到结果相同为止（strcmp 0 - 相同 1 - 不同）
	while (p && strcmp(p->str, str)) p = p->next;
	return p != NULL;
}

void clearNode(Node *node) {
	if (node == NULL) return;
	Node *p = node, *q;
	while (p) {
		q = p->next;
		free(p->str);
		free(p);
		p = q;
	}
	return;
}

void clear(HashTable *h) {
	if (h == NULL) return;
	for (int i = 0; i < h->size; i++) {
		clearNode(h->data[i]);
	}
	free(h->data);
	free(h);
	return;
}
