//
//  队列 Queue
//
//  Created by 巫瑞轩 on 2021/9/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct queue {
	int *data;
	int head, tail, length, count;
} Queue;

Queue *init(int);
void clear(Queue *);
int push(Queue *, int);
int pop(Queue *);
int isEmpty(Queue *);
int front(Queue *);
int expand(Queue *);
void output(Queue *);

int main(int argc, char const *argv[])
{
	srand(time(0));
	#define MAX_OP 20
	Queue *q = init(1);
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

// 初始化
Queue *init(int n) {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->data = (int *)malloc(sizeof(int) * n);
	q->length = n;
	q->head = q->tail = 0;
	q->count = 0;
	return q;
}

// 销毁
void clear(Queue *q) {
	if (q == NULL) return;
	free(q->data);
	free(q);
	return;
}

// 入队
int push(Queue *q, int val) {
	if (q == NULL) return 0;
	if (q->count == q->length) {
		if (!expand(q)) return 0;
		printf("success to expand! the size = %d\n", q->length);
	}
	q->data[q->tail++] = val;
	// 解决假溢出（队首指针走到队尾指针处，导致无法继续入队元素）
	if (q->tail == q->length) q->tail = 0;
	q->count += 1;
	return 1;
}

// 出队
int pop(Queue *q) {
	if (q == NULL) return 0;
	if (isEmpty(q)) return 0;
	q->head += 1;
	if (q->head == q->length) q->head = 0;
	q->count -= 1;
	return 1;
}

// 判断队列是否为空
int isEmpty(Queue *q) {
	return q->count == 0;
}

// 获取队首元素
int front(Queue *q) {
	return q->data[q->head];
}

// 扩容
int expand(Queue *q) {
	int extraSize = q->length;
	int *p;
	while (extraSize) {
		// 尝试申请开辟大于原空间大小的新空间，如果申请失败，则p为NULL
		p = (int *)malloc(sizeof(int) * (q->length + extraSize));
		// 申请的空间太大，缩小（减半）要申请的额外空间大小，重新尝试
		if (p != NULL) break;
		// 等同于 extraSize /= 2
		extraSize >>= 1;
	}
	// 没有剩余空间可以开辟
	if (p == NULL) return 0;
	// 将原队列中的元素拷贝到新开辟的空间中去
	for (int i = q->head, j = 0; j < q->count; j++) {
		p[j] = q->data[(i + j) % q->length];

	}
	free(q->data);
	q->data = p;
	q->head = 0, q->tail = q->count;
	q->length += extraSize;
	return 1;
}

// 输出
void output(Queue *q) {
	printf("Queue: [");
	for (int i = q->head, j = 0; j < q->count; j++) {
		j && printf(" ");
		printf("%d", q->data[(i + j) % q->length]);
	}
	printf("]\n");
	return;
}
