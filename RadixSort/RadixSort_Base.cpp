#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void PrintArr(int* a, int n)	// 打印
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int GetMax(int* a, int n)	// 获取数组中最大的位数
{
	int count = 1;
	int max = a[0];
	for (int i = 0; i < n; i++)
		if (a[i] > max)
			max = a[i];
	while (max / 10)
	{
		count++;
		max = max / 10;
	}
	return count;
}

void RadixSort2(int* a, int n, int exp)
{
	int* bucket[10] = {};
	int count[10] = { 0 };	// 代表10个桶里面分别有多少个数字了。
	for (int i = 0; i < 10; i++)
		bucket[i] = (int*)malloc(sizeof(int) * n);	// 辅助数组
	for (int i = 0; i < n; i++)
	{
		int index = a[i] / exp % 10;
		bucket[index][count[index]] = a[i];
		count[index] ++;
	}
	int k = 0;
	for (int i = 0; i < 10; i++)	// 还原到数组中
	{
		for (int j = 0; j < count[i]; j++)
		{
			a[k] = bucket[i][j];
			k++;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		free(bucket[i]);	// 释放辅助数组
		bucket[i] = NULL;
	}
}

void RadixSort1(int* a, int n)
{
	int MaxCount = GetMax(a, n);	// 获取最大位数
	//printf("%d", max);
	int exp = 1;
	for (int i = 0; i < MaxCount; i++)	// 循环max_count次即可
	{
		RadixSort2(a, n, exp);
		exp *= 10;
	}
}

void RadixSort(int* a, int n)
{
	int NegativeCount = 0;
	for (int i = 0; i < n; i++)	// 统计出负数的个数
	{
		if (a[i] < 0)
			NegativeCount++;
	}
	int* NegativeArr = (int*)malloc(sizeof(int) * NegativeCount);
	int* PositiveArr = (int*)malloc(sizeof(int) * (n - NegativeCount));
	int k = 0;
	int j = 0;
	for (int i = 0; i < n; i++)	// 将正数负数各自放到一个数组中
	{
		if (a[i] < 0)
		{
			NegativeArr[j] = 0 - a[i];	// 负数先转换为正数

			j++;
		}
		else
		{
			PositiveArr[k] = a[i];	
			k++;
		}
	}
	RadixSort1(NegativeArr, j);	// 对负数进行排序
	RadixSort1(PositiveArr, k);	// 对正数进行排序
	for (int i = 0; i < j; i++)
		a[i] = 0 - NegativeArr[j - i - 1];	// 逆向输出负数
	for (int i = 0; i < k; i++)
		a[i + j] = PositiveArr[i];
	free(NegativeArr);
	free(PositiveArr);
	NegativeArr = NULL;
	PositiveArr = NULL;
}

void main()
{
	//int a[11] = { 0, -1900, -1,3,542, 748,0,214,154,63,616 };
	//PrintArr(a, 11);
	//int a[10] = { 53, 3, 542 };
	int size = 10000 * 10000;
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
	clock_t start, end;
	srand((unsigned int)time(NULL));
	start = clock();
	RadixSort(arr, size);
	end = clock();
	printf("花费时间：%f\n", (double)(end - start) / CLK_TCK);
	for (int i = 0; i < size; ++i)
	{
		//printf("%d \n",arr[i]);
		if (i > 0 && arr[i - 1] > arr[i])
			printf("wrong %d %d\n", arr[i - 1], arr[i]);
	}
}