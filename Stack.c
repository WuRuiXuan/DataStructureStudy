//
//  栈 Stack
//
//  Created by 巫瑞轩 on 2021/9/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stack {
	int *data;
	int top, size;
} Stack;

Stack *init(int);
void clear(Stack *);
int push(Stack *, int);
int pop(Stack *);
int isEmpty(Stack *);
int top(Stack *);
int expand(Stack *);
void output(Stack *);

int main(int argc, char const *argv[])
{
	srand(time(0));
	#define MAX_OP 20
	Stack *s = init(1);
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

Stack *init(int n) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data = (int *)malloc(sizeof(int) * n);
	s->size = n;
	s->top = -1;
	return s;
}

void clear(Stack *s) {
	if (s == NULL) return;
	free(s->data);
	free(s);
	return;
}

int push(Stack *s, int val) {
	if (s == NULL) return 0;
	if (s->top == s->size - 1) {
		if (!expand(s)) return 0;
		printf("success to expand! the size = %d\n", s->size);
	}
	s->data[++(s->top)] = val;
	return 1;
}

int pop(Stack *s) {
	if (s == NULL) return 0;
	if (isEmpty(s)) return 0;
	s->top -= 1;
	return 1;
}

int isEmpty(Stack *s) {
	return s->top == -1;
}

int top(Stack *s) {
	return s->data[s->top];
}

int expand(Stack *s) {
	int extraSize = s->size;
	int *p;
	while (extraSize) {
		p = (int *)realloc(s->data, sizeof(int) * (s->size + extraSize));
		if (p != NULL) break;
		extraSize >>= 1;
	}
	if (p == NULL) return 0;
	s->data = p;
	s->size += extraSize;
	return 1;
}

void output(Stack *s) {
	printf("Stack: [");
	for (int i = 0; i <= s->top; i++) {
		i && printf(" ");
		printf("%d", s->data[i]);
	}
	printf("]\n");
	return;
}
