//
//  顺序表 Vector
//
//  Created by 巫瑞轩 on 2021/8/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 结构定义
typedef struct vector {
    int *data;
    int size, length;
} Vector;

// 结构操作
Vector *init(int);
void clear(Vector *);
int expand(Vector *);
int insert(Vector *, int, int);
int erase(Vector *, int);
void output(Vector *);

int main(int argc, char const *argv[]) {
    // 使用随机函数必须先初始化随机数发生器(需要引入time.h)
    srand(time(0));
    // 随机执行操作的次数
    #define MAX_OP 20
    Vector *v = init(1);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4;
        int val = rand() % 100;
        // -1 ~ length+1
        int idx = rand() % (v->length + 3) - 1;
        switch (op) {
            case 0:
            case 1:
            case 2:
            {
                printf("insert %d at %d to Vector = %d\n", val, idx, insert(v, idx, val));
            }
                break;
            case 3:
            {
                printf("erase a item at %d from Vector = %d\n", idx, erase(v, idx));
            }
            default:
                break;
        }
        output(v);
        printf("\n");
    }
    return 0;
}

// 初始化
Vector *init(int n) {
    // 动态申请内存空间，需要主动释放
    Vector *v = (Vector *)malloc(sizeof(Vector));
    // 申请内存空间用于存储整型数据
    v->data = (int *)malloc(sizeof(int) * n);
    v->size = n;
    v->length = 0;
    return v;
}

// 销毁
void clear(Vector *v) {
    if (v == NULL) return;
    // malloc calloc realloc 开辟的内存空间都需要手动释放
    free(v->data);
    free(v);
    return;
}

// 扩容
int expand(Vector *v) {
    int extraSize = v->size;
    int *p;
    while (extraSize) {
        p = (int *)realloc(v->data, sizeof(int) * (v->size + extraSize));
        if (p != NULL) break;
        // 等同于 extraSize /= 2
        extraSize >>= 1;
    }
    // 没有剩余空间可以开辟
    if (p == NULL) return 0;
    v->data = p;
    v->size += extraSize;
    return 1;
}

// 插入
int insert(Vector *v, int idx, int val) {
    if (v == NULL) return 0;
    if (v->length == v->size) {
        if (!expand(v)) return 0;
        printf("success to expand! the size = %d\n", v->size);
    }
    if (idx < 0 || idx > v->length) return 0;
    // 从末尾开始依次往前挪，反之则会出现后面挪动的值被第一个挪动的值所覆盖的情况
    for (int i = v->length; i > idx; i--) {
        v->data[i] = v->data[i - 1];
    }
    v->data[idx] = val;
    v->length += 1;
    return 1;
}

// 删除
int erase(Vector *v, int idx) {
    if (v == NULL) return 0;
    if (idx < 0 || idx >= v->length) return 0;
    // 从删除位置开始，依次往后用后面的值覆盖前面的值
    for (int i = idx; i < v->length - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->length -= 1;
    return 1;
}

// 输出
void output(Vector *v) {
    if (v == NULL) return;
    printf("Vector: [");
    for (int i = 0; i < v->length; i++) {
        // 如果不是第一个元素就先打印一个空格
        i && printf(" ");
        printf("%d", v->data[i]);
    }
    printf("]\n");
    return;
}
