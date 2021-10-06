//
//  非稳定排序 UnstableSort
//
//  Created by 巫瑞轩 on 2021/10/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 选择排序可能出现a、b是同一个的情况，因此不能用异或的方法去交换两个变量的值
#define swap(a, b) {\
	__typeof(a) __temp = a;\
	a = b; b = __temp;\
}

#define test(arr, n, func, args...) {\
	int *num = (int *)malloc(sizeof(int) * n);\
	memcpy(num, arr, sizeof(int) * n);\
	output(num, n);\
	printf("%s = ", #func);\
	func(args);\
	output(num, n);\
	free(num);\
}

void randint(int *, int);
void output(int *, int);
void selectSort(int *, int);
void quickSort(int *, int, int);

int main(int argc, char const *argv[])
{
	srand(time(0));
	#define MAX_N 20
	int arr[MAX_N];
	randint(arr, MAX_N);
	test(arr, MAX_N, selectSort, num, MAX_N);
	test(arr, MAX_N, quickSort, num, 0, MAX_N - 1);
	#undef MAX_N
	return 0;
}

// 给数组每一项赋随机值
void randint(int *num, int n) {
	while (n--) num[n] = rand() % 100;
}

// 输出数组
void output(int *num, int n) {
	printf("[");
	for (int i = 0; i < n; ++i)
	{
		i && printf(" ");
		printf("%d", num[i]);
	}
	printf("]\n");
	return;
}

// 选择排序(n^2)：从头到尾扫描待排序区，找出最小的元素放到已排序区的末尾，然后不断重复这一过程，直到待排序区没有元素为止
void selectSort(int *num, int n) {
	for (int i = 0; i < n - 1; ++i)
	{
		int idx = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (num[j] < num[idx]) idx = j;
		}
		swap(num[idx], num[i]);
	}
	return;
}

// 快速排序(nlogn - n^2)
void quickSort(int *num, int l, int r) {
	if (l > r) return;
	// z - 基准值
	int x = l, y = r, z = num[x];
	while (x < y) {
		while (x < y && num[y] > z) y--;
		if (x < y) num[x++] = num[y];
		while (x < y && num[x] < z) x++;
		if (x < y) num[y--] = num[x]; 
	}
	num[x] = z;
	quickSort(num, l, x - 1);
	quickSort(num, x + 1, r);
	return;
}
