#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void PrintArr(int* a, int n)	// ��ӡ
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int GetMax(int* a, int n)	// ��ȡ����������λ��
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
	int count[10] = { 0 };	// ����10��Ͱ����ֱ��ж��ٸ������ˡ�
	for (int i = 0; i < 10; i++)
		bucket[i] = (int*)malloc(sizeof(int) * n);	// ��������
	for (int i = 0; i < n; i++)
	{
		int index = a[i] / exp % 10;
		bucket[index][count[index]] = a[i];
		count[index] ++;
	}
	int k = 0;
	for (int i = 0; i < 10; i++)	// ��ԭ��������
	{
		for (int j = 0; j < count[i]; j++)
		{
			a[k] = bucket[i][j];
			k++;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		free(bucket[i]);	// �ͷŸ�������
		bucket[i] = NULL;
	}
}

void RadixSort1(int* a, int n)
{
	int MaxCount = GetMax(a, n);	// ��ȡ���λ��
	//printf("%d", max);
	int exp = 1;
	for (int i = 0; i < MaxCount; i++)	// ѭ��max_count�μ���
	{
		RadixSort2(a, n, exp);
		exp *= 10;
	}
}

void RadixSort(int* a, int n)
{
	int NegativeCount = 0;
	for (int i = 0; i < n; i++)	// ͳ�Ƴ������ĸ���
	{
		if (a[i] < 0)
			NegativeCount++;
	}
	int* NegativeArr = (int*)malloc(sizeof(int) * NegativeCount);
	int* PositiveArr = (int*)malloc(sizeof(int) * (n - NegativeCount));
	int k = 0;
	int j = 0;
	for (int i = 0; i < n; i++)	// �������������Էŵ�һ��������
	{
		if (a[i] < 0)
		{
			NegativeArr[j] = 0 - a[i];	// ������ת��Ϊ����

			j++;
		}
		else
		{
			PositiveArr[k] = a[i];	
			k++;
		}
	}
	RadixSort1(NegativeArr, j);	// �Ը�����������
	RadixSort1(PositiveArr, k);	// ��������������
	for (int i = 0; i < j; i++)
		a[i] = 0 - NegativeArr[j - i - 1];	// �����������
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
	printf("����ʱ�䣺%f\n", (double)(end - start) / CLK_TCK);
	for (int i = 0; i < size; ++i)
	{
		//printf("%d \n",arr[i]);
		if (i > 0 && arr[i - 1] > arr[i])
			printf("wrong %d %d\n", arr[i - 1], arr[i]);
	}
}