//
//  二分查找 BinarySearch
//
//  Created by 巫瑞轩 on 2021/10/31.
//

#include <stdio.h>

int binarySearch(int *, int, int);
int binarySearch1(int *, int);
int binarySearch2(int *, int);

int main(int argc, char const *argv[])
{
	int arr[100] = {0}, n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", arr + i);
	}
	// 标准二分查找
	// int x;
	// while (~scanf("%d", &x)) {
	// 	printf("%d\n", binarySearch(arr, n, x));
	// }
	// 特殊情况1
	// printf("%d\n", binarySearch1(arr, n));
	// 特殊情况2
	printf("%d\n", binarySearch2(arr, n));
	return 0;
}

int binarySearch(int *arr, int n, int x) {
	int head = 0, tail = n - 1, mid;
	while (head <= tail) {
		mid = (head + tail) >> 1;
		if (arr[mid] == x) return mid;
		if (arr[mid] <= x) head = mid + 1;
		else tail = mid - 1;
	}
	return -1;
}

// 特殊情况1：0000011111 找第一个1
int binarySearch1(int *arr, int n) {
	// 虚拟尾指针指向最后一个元素的后一个位置
	int head = 0, tail = n, mid;
	while (head < tail) {
		mid = (head + tail) >> 1;
		if (arr[mid] == 1) tail = mid;
		else head = mid + 1;
	}
	return head == n ? -1 : head;
}

// 特殊情况2：1111100000 找最后一个1
int binarySearch2(int *arr, int n) {
	// 虚拟头指针指向第一个元素的前一个位置
	int head = -1, tail = n - 1, mid;
	while (head < tail) {
		// 向上取整避免死循环
		mid = (head + tail + 1) >> 1;
		if (arr[mid] == 1) head = mid;
		else tail = mid - 1;
	}
	return head;
}
