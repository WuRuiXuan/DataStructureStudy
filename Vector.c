//
//  顺序表
//  CStudy
//
//  Created by 巫瑞轩 on 2021/8/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 结构定义
typedef struct Vector {
    int *data;
    int size, length;
} Vector;

// 结构操作
Vector *m_init(int);
void m_clear(Vector *);
int m_insert(Vector *, int, int);
int m_erase(Vector *, int);
void m_output(Vector *);

int main() {
    // 使用随机函数必须先初始化随机数发生器(需要引入time.h)
    srand(time(0));
    #define MAX_OP 20
    Vector *v = m_init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 2;
        int val = rand() % 100;
        int idx = rand() % (v->length + 3) - 1;
        switch (op) {
            case 0:
            {
                printf("insert %d at %d to Vector = %d\n", val, idx, m_insert(v, idx, val));
            }
                break;
            case 1:
            {
                printf("erase a item at %d from Vector = %d\n", idx, m_erase(v, idx));
            }
            default:
                break;
        }
        m_output(v);
    }
    return 0;
}

// 初始化
Vector *m_init(int n) {
    // 动态申请内存空间，需要主动释放
    Vector *v = (Vector *)malloc(sizeof(Vector));
    // 申请内存空间用于存储整型数据
    v->data = (int *)malloc(sizeof(int) * n);
    v->size = n;
    v->length = 0;
    return v;
}

// 销毁
void m_clear(Vector *v) {
    if (v == NULL) return;
    // malloc calloc realloc 开辟的内存空间都需要手动释放
    free(v->data);
    free(v);
    return;
}

// 插入
int m_insert(Vector *v, int idx, int val) {
    if (v == NULL) return 0;
    if (v->length == v->size) return 0;
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
int m_erase(Vector *v, int idx) {
    if (v == NULL) return 0;
    if (idx < 0 || idx > v->length) return 0;
    for (int i = idx; i < v->length; i++) {
        v->data[i] = v->data[i+1];
    }
    v->length -= 1;
    return 1;
}

// 输出
void m_output(Vector *v) {
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
