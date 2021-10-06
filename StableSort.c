//
//  稳定排序 StableSort
//
//  Created by 巫瑞轩 on 2021/10/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a, b) {\
	a ^= b; b ^= a; a ^= b;\
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
void insertSort(int *, int);
void bubbleSort(int *, int);
void mergeSort(int *, int, int);

int main(int argc, char const *argv[])
{
	srand(time(0));
	#define MAX_N 20
	int arr[MAX_N];
	randint(arr, MAX_N);
	test(arr, MAX_N, insertSort, num, MAX_N);
	test(arr, MAX_N, bubbleSort, num, MAX_N);
	test(arr, MAX_N, mergeSort, num, 0, MAX_N - 1);
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

// 插入排序(n^2)：不断将待排序区第一个元素插入到已排序区，在已排序区从尾到头扫描，直到找到第一个比待插入元素小的元素，将待插入元素插入到该元素的后面
void insertSort(int *num, int n) {
	for (int i = 1; i < n; ++i)
	{
		for (int j = i; j > 0 && num[j] < num[j - 1]; j--)
		{
			// 通过不断交换来挪动待插入元素的位置，直到前一个元素比待插入元素小为止
			swap(num[j], num[j - 1]);
		}
	}
	return;
}

// 冒泡排序(n^2)：从头到尾扫描，每次找出待排序区最大的元素放到已排序区的开头，直到待排序区没有元素为止
void bubbleSort(int *num, int n) {
	// 记录每一轮冒泡出现交换的次数，如果一次交换都没有出现过，则不需要继续排序
	int times = 1;
	for (int i = 1; i < n && times; ++i)
	{
		times = 0;
		for (int j = 0; j < n - i; ++j)
		{
			if (num[j] <= num[j + 1]) continue;
			swap(num[j], num[j + 1]);
			times++;
		}
	}
	return;
}

// 二路归并排序(nlogn)：对原始数组不断进行折半拆分，直到拆成多组（两两一组）元素个数为2或3的数组，再对每个数组进行排序，最后把所有数组按照从小到大的顺序合并成一个数组
void mergeSort(int *num, int l, int r) {
	if (r - l <= 1) {
		if (r - l == 1 && num[r] < num[l]) {
			swap(num[r], num[l]);
		}
		return;
	}
	int mid = (l + r) >> 1;
	mergeSort(num, l, mid);
	mergeSort(num, mid + 1, r);
	int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
	int p1 = l, p2 = mid + 1, k = 0;
	while (p1 <= mid || p2 <= r) {
		if (p2 > r || (p1 <= mid && num[p1] <= num[p2])) {
			temp[k++] = num[p1++];
		}
		else {
			temp[k++] = num[p2++];
		}
	}
	memcpy(num + l, temp, sizeof(int) * (r - l + 1));
	free(temp);
	return;
}
